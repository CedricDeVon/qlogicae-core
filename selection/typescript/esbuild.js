import { Glob } from 'bun';
import { build } from 'esbuild';
import { mkdir } from 'node:fs/promises';

await mkdir('./output/build/v1', {
	recursive: true
});

const entry_points = ['index.ts'];

for await (const file of new Glob('**/*.ts').scan('v1')) {
	entry_points.push(`v1/${file}`);
}

await build({
	entryPoints: entry_points,
	outbase: '.',
	outdir: './output/build',
	bundle: false,
	format: 'esm',
	platform: 'neutral',
	target: 'esnext',
	sourcemap: true
});
