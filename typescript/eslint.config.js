import js from '@eslint/js';
import tseslint from 'typescript-eslint';

export default tseslint.config(
	{
		ignores: [
			'node_modules/**',
			'.build/**',
			'.builds/**',
			'build/**',
			'builds/**',
			'.dist/**',
			'.dists/**',
			'dist/**',
			'dists/**',
			'.output/**',
			'.outputs/**',
			'output/**',
			'outputs/**',
			'.coverage/**',
			'.coverages/**',
			'coverage/**',
			'coverages/**',
			'.report/**',
			'.reports/**',
			'report/**',
			'reports/**',
			'.temp/**',
			'.temporary/**',
			'temp/**',
			'temporary/**'
		]
	},

	js.configs.recommended,
	...tseslint.configs.recommended,

	{
		files: ['**/*.ts'],
		rules: {}
	}
);
