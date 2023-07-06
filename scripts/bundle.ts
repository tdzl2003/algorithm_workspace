import * as fs from 'fs';
import * as path from 'path';
import { Readable } from 'stream';

const processedMap = new Set<string>();

function* processFile(fn: string) {
  const data = fs.readFileSync(fn, 'utf-8');
  for (const line of data.split('\n')) {
    if (line == '#pragma once') {
      if (processedMap.has(fn)) {
        return;
      }
      processedMap.add(fn);
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
    yield line + '\n';
  }
}

async function main(input: string, output: string) {
  const outputStream = fs.createWriteStream(output, 'utf-8');
  Readable.from(processFile(path.resolve(input)))
    .pipe(outputStream)
    .on('finish', () => {
      console.log('Done.');
    });
}

main(process.argv[2], process.argv[3]);
