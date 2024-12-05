import { readFileSync } from "fs";

const input = readFileSync(
  "/home/marcus/Documents/coding/advent-of-code/2024/inputs/3.txt",
  { encoding: "utf-8" },
);

const testInput =
  "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

/**
 * @param input {string}
 */
function isDigit(input) {
  const code = input.charCodeAt(0);
  return code >= 48 && code <= 57;
}

function solveOne(input) {
  let total = 0;
  let inputOne = 0;
  let inputTwo = 0;
  let accumulator = "";
  const STATE = {
    DISABLED: "disabled",
    SEARCHING: "searching",
    OP_1: "op_1",
    OP_2: "op_2",
  };
  let currentState = STATE.SEARCHING;

  function reset() {
    inputOne = 0;
    inputTwo = 0;
    accumulator = "";
    currentState = STATE.SEARCHING;
  }

  for (let i = 0; i < input.length; i++) {
    const char = input[i];
    console.log("%s '%s'", currentState, char);
    switch (currentState) {
      case STATE.SEARCHING:
        if (char === "m") {
          const expected = "mul(";
          const actual = input.slice(i, i + 4);
          if (expected === actual) {
            i += 3;
            currentState = STATE.OP_1;
          }
        }
        break;
      case STATE.MUL:
        const expected = "ul(";
        const actual = input.slice(i, i + 3);
        console.log({ expected, actual });
        if (expected === actual) {
          currentState = STATE.OP_1;
          i += 2;
          break;
        }
        reset();
        break;
      case STATE.OP_1:
        if (isDigit(char)) {
          accumulator += char;
          break;
        }
        if (char === ",") {
          inputOne = parseInt(accumulator, 10);
          accumulator = "";
          currentState = STATE.OP_2;
          break;
        }
        reset();
        break;
      case STATE.OP_2:
        if (isDigit(char)) {
          accumulator += char;
          break;
        }
        if (char === ")") {
          inputTwo = parseInt(accumulator, 10);
          total += inputOne * inputTwo;
          reset();
          break;
        }
        reset();
        break;
    }
  }
  return total;
}

function solveTwo(input) {
  let total = 0;
  let inputOne = 0;
  let inputTwo = 0;
  let accumulator = "";
  const STATE = {
    DISABLED: "disabled",
    SEARCHING: "searching",
    OP_1: "op_1",
    OP_2: "op_2",
  };
  let currentState = STATE.SEARCHING;

  function reset() {
    inputOne = 0;
    inputTwo = 0;
    accumulator = "";
    currentState = STATE.SEARCHING;
  }

  for (let i = 0; i < input.length; i++) {
    const char = input[i];
    console.log("%s '%s'", currentState, char);
    switch (currentState) {
      case STATE.DISABLED:
        if (char === "d") {
          const expected = "do()";
          const actual = input.slice(i, i + 4);
          if (actual === expected) {
            i += 3;
            currentState = STATE.SEARCHING;
            break;
          }
        }
        break;
      case STATE.SEARCHING:
        if (char === "m") {
          const expected = "mul(";
          const actual = input.slice(i, i + 4);
          if (expected === actual) {
            i += 3;
            currentState = STATE.OP_1;
          }
        }
        if (char === "d") {
          const expected = "don't()";
          const actual = input.slice(i, i + 7);
          if (actual === expected) {
            i += 6;
            currentState = STATE.DISABLED;
            break;
          }
        }
        break;
      case STATE.MUL:
        const expected = "ul(";
        const actual = input.slice(i, i + 3);
        console.log({ expected, actual });
        if (expected === actual) {
          currentState = STATE.OP_1;
          i += 2;
          break;
        }
        reset();
        break;
      case STATE.OP_1:
        if (isDigit(char)) {
          accumulator += char;
          break;
        }
        if (char === ",") {
          inputOne = parseInt(accumulator, 10);
          accumulator = "";
          currentState = STATE.OP_2;
          break;
        }
        reset();
        break;
      case STATE.OP_2:
        if (isDigit(char)) {
          accumulator += char;
          break;
        }
        if (char === ")") {
          inputTwo = parseInt(accumulator, 10);
          total += inputOne * inputTwo;
          reset();
          break;
        }
        reset();
        break;
    }
  }
  return total;
}
console.log(solveTwo(input));
