import * as fs from 'fs';
import * as path from 'path';
import { Readable } from 'stream';

const processedMap = new Set<string>();
const processedLibMap = new Set<string>();

function* processFile(fn: string) {
  const data = fs.readFileSync(fn, 'utf-8');
  for (const t of data.split('\n')) {
    const line = t.trim();
    if (line == '#pragma once') {
      if (processedMap.has(fn)) {
        return;
      }
      processedMap.add(fn);
      continue;
    }
    if (line.startsWith('//') || !line) {
      continue;
    }
    const m = /^#include "(.*)"$/.exec(line);
    if (m) {
      if (path.isAbsolute(m[1])) {
        yield* processFile(path.resolve('./cpp', m[1]));
      } else {
        yield* processFile(path.resolve(path.dirname(fn), m[1]));
      }
      continue;
    }
    const m1 = /^#include <(.*)>$/.exec(line);
    if (m1) {
      if (processedLibMap.has(m1[1])) {
        continue;
      }
      processedLibMap.add(m1[1]);
      yield t + '\n';
      continue;
    }

    yield t + '\n';
  }
}

async function bundle(input: string, output: string) {
  processedMap.clear();
  processedLibMap.clear();
  const outputStream = fs.createWriteStream(output, 'utf-8');
  console.log('Bundling...');
  outputStream.write(`#ifndef ONLINE_JUDGE
#define ONLINE_JUDGE
#endif
`);
  Readable.from(processFile(path.resolve(input)))
    .on('error', (err) => {
      console.warn(err.stack);
      console.log('Bundle failed.');
    })
    .on('end', () => {
      console.log('Bundled.');
    })
    .pipe(outputStream);
}

const mainFn = './cpp/main.cpp';
const bundleFn = './bundled/bundled.cpp';

async function main() {
  const watcher = fs.promises.watch('./cpp', {
    recursive: true,
  });
  let timer = null;
  let bundling = false,
    pending = false;
  console.log('Watching...');

  async function doBundle() {
    if (pending) {
      return;
    }
    pending = true;
    while (bundling) {
      await new Promise((resolve) => setTimeout(resolve, 1000));
    }
    bundling = true;
    try {
      await bundle(mainFn, bundleFn);
    } catch (e) {
      console.warn(e.stack);
    }
    bundling = false;
    pending = false;
  }
  doBundle();

  for await (const event of watcher) {
    if (event.eventType != 'change' || !/\.[ch]pp$/.test(event.filename)) {
      continue;
    }
    if (timer) {
      clearTimeout(timer);
    }
    timer = setTimeout(doBundle, 500);
  }
}

main();
