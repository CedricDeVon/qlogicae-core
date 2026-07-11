import baseConfig from './vitest.config';
import { mergeConfig } from 'vitest/config';

const now = new Date();
const iso = now
	.toISOString()
	.replace(/:/g, '')
	.replace(/\.\d+Z$/, '');
const ns = process.hrtime.bigint().toString().slice(-9);

export default mergeConfig(baseConfig, {
	test: {
		coverage: {
			reportsDirectory: `./output/test/benchmark/${iso}-${ns}Z`
		},
		include: ['./test/v1/benchmark/**/*.bench.ts']
	}
});
