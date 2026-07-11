#!/usr/bin/env bun

import data from './package.json' with { type: 'json' };

console.log(`${data.version}`);
