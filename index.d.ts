declare module 'cmatrix' {
    export class JMatrix {
        constructor(rows: number, cols: number, initValue: number);
        public setCell(row: number, col: number, value: number): void;
        public mds(dimensions: number, max_iter: number): number[][];
    }
}