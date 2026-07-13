#!/usr/bin/env node

import data from './package.json' with { type: 'json' };

console.log(`${data.version}`);
