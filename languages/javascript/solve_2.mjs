import { readFileSync } from "fs";

const file = readFileSync(
  "/home/marcus/Documents/coding/advent-of-code/2024/inputs/2.txt",
  { encoding: "utf-8" },
);

/**
 * @param input {string}
 */
function validateLine(input) {
  const nums = input.split(" ").map((numberString) => parseInt(numberString));
  let isAscending = null;

  for (let i = 0; i < nums.length - 1; i++) {
    const numOne = nums[i];
    const numTwo = nums[i + 1];
    if (i == 0) {
      isAscending = nums[i] < nums[i + 1];
    }
    const diff = Math.abs(numOne - numTwo);
    const isDirectionValid = isAscending === nums[i] < nums[i + 1];
    const isIntervalValid = 1 <= diff && diff <= 3;
    if (!isDirectionValid || !isIntervalValid) {
      return false;
    }
  }
  return true;
}

/**
 * @param input {string}
 */
function validateLineTwo(input) {
  let canSkip = true;
  const nums = input.split(" ").map((numberString) => parseInt(numberString));
  let isAscending = null;

  for (let i = 0; i < nums.length - 1; i++) {
    const numOne = nums[i];
    const numTwo = nums[i + 1];
    if (i == 0) {
      isAscending = nums[i] < nums[i + 1];
    }
    const diff = Math.abs(numOne - numTwo);
    const isDirectionValid = isAscending === nums[i] < nums[i + 1];
    const isIntervalValid = 1 <= diff && diff <= 3;
    if (!isIntervalValid && canSkip) {
      canSkip = false;
      continue;
    }
    if (!isDirectionValid || !isIntervalValid) {
      return false;
    }
  }
  return true;
}

const lines = file.split("\n").filter(Boolean);
const safeLines = lines.reduce((acc, line) => {
  return validateLine(line) ? acc + 1 : acc;
}, 0);
console.log(safeLines);

const safeLinesTwo = lines.reduce((acc, line) => {
  return validateLineTwo(line) ? acc + 1 : acc;
}, 0);

console.log(safeLinesTwo);
