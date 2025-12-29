import fs from "fs";

function parse(rot) {
    const dir = rot[0];
    const value = parseInt(rot.slice(1), 10);

    if (dir === "L") return -value;
    if (dir === "R") return value;
}

function parseLines(src) {
    return src
        .split(/\r?\n/)
        .map((s) => s.trim())
        .filter((s) => s.length > 0)
        .map(parse);
}

function part01(data) {
    let dial = 50;
    let counter = 0;

    for (const d of data) {
        dial += d;
        if (dial % 100 === 0) {
            counter++;
        }
    }

    return counter;
}

function part02(data) {
    let dial = 50;
    let counter = 0;

    for (const d of data) {
        const wholeTurns = Math.floor(Math.abs(d) / 100);

        const dd = d % 100;

        let partialTurn = 0;

        if (dd > 0) {
            // R: crossing 100 -> 0
            partialTurn = dial < 100 && dial + dd >= 100 ? 1 : 0;
        } else if (dd < 0) {
            // L: crossing 1 -> 0
            partialTurn = dial >= 1 && dial + dd <= 0 ? 1 : 0;
        }

        counter += wholeTurns + partialTurn;
        dial = ((dial + d) % 100 + 100) % 100;
    }

    return counter;
}

if (process.argv[1] === new URL(import.meta.url).pathname) {
    const src = fs.readFileSync(process.argv[2], "utf-8");
    const input = parseLines(src);

    console.log("P1:", part01(input));
    console.log("P2:", part02(input));
}
