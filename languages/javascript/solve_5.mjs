import assert from "assert";
import { readFileSync } from "fs";

const file = readFileSync(
  "/home/marcus/Documents/coding/advent-of-code/2024/inputs/5.txt",
  { encoding: "utf-8" },
);

/**
 * @param input {string}
 * @returns {[Map<number, {before: number[], after: number[]}>,number[][]]}
 */
function parseInput(input) {
  const [rulesString, data] = input.split("\n\n");
  const ruleMap = rulesString
    .trim()
    .split("\n")
    .reduce((acc, line) => {
      let [beforeString, afterString] = line.trim().split("|");
      let beforeNumber = parseInt(beforeString, 10);
      let afterNumber = parseInt(afterString, 10);
      let beforeEntry = acc.get(beforeNumber) ?? { before: [], after: [] };
      let afterEntry = acc.get(afterNumber) ?? { before: [], after: [] };
      beforeEntry.after.push(afterNumber);
      afterEntry.before.push(beforeNumber);
      acc.set(beforeNumber, beforeEntry);
      acc.set(afterNumber, afterEntry);
      return acc;
    }, new Map());
  const dataNumbers = data
    .trim()
    .split("\n")
    .map((line) =>
      line
        .trim()
        .split(",")
        .map((entry) => parseInt(entry, 10)),
    );
  return [ruleMap, dataNumbers];
}

/**
 * @param map {Map<number, {before: number[], after: number[]}>}
 * @param data {number[]}
 */
function isValidLine(map, data) {
  return data.every((num, index, arr) => {
    const before = arr.slice(0, index);
    const after = arr.slice(index + 1);
    const rules = map.get(num);
    if (!rules) {
      return true;
    }
    const isBeforeValid = before.every(
      (beforeNum) => !rules.after.includes(beforeNum),
    );
    const isAfterValid = after.every(
      (afterNum) => !rules.before.includes(afterNum),
    );
    return isBeforeValid && isAfterValid;
  });
}

function partOne(input) {
  const [ruleMap, data] = parseInput(input);
  const validData = data.filter((entry) => isValidLine(ruleMap, entry));
  const total = validData.reduce((acc, dataLine) => {
    const middleValue = dataLine[Math.floor(dataLine.length / 2)];
    return acc + middleValue;
  }, 0);
  return total;
}

/**
 * @param map {Map<number, {before: number[], after: number[]}>}
 * @param data {number[]}
 */
function reorderLine(map, data) {
  assert(Array.isArray(data));
  const { inValidData, validData } = data.reduce(
    (acc, num, index, arr) => {
      const before = arr.slice(0, index);
      const after = arr.slice(index + 1);
      const rules = map.get(num);
      if (!rules) {
        return true;
      }
      const isBeforeValid = before.every(
        (beforeNum) => !rules.after.includes(beforeNum),
      );
      const isAfterValid = after.every(
        (afterNum) => !rules.before.includes(afterNum),
      );
      const isValid = isBeforeValid && isAfterValid;
      if (isValid) {
        acc.validData.push(num);
        return acc;
      }
      acc.inValidData.push(num);
      return acc;
    },
    {
      inValidData: [],
      validData: [],
    },
  );
  console.log({ data, validData, inValidData });
  if (inValidData.length === 0) {
    return validData;
  }
  const newArray = inValidData.reduce((acc, cur) => {
    const entry = map.get(cur);
    const beforeIndex = entry.before.reduce((indexAcc, beforeNum) => {
      const index = acc.indexOf(beforeNum);
      if (index != -1) {
        return Math.max(index + 1, indexAcc);
      }
      return indexAcc;
    }, 0);
    const maxIndex = beforeIndex;
    const beforeSlice = acc.slice(0, maxIndex);
    const afterSlice = acc.slice(maxIndex);
    const output = [...beforeSlice, cur, ...afterSlice];
    console.log({
      acc,
      cur,
      beforeRules: entry.before,
      afterRules: entry.after,
      beforeIndex,
      maxIndex,
      beforeSlice,
      afterSlice,
      output,
    });
    return output;
  }, validData);
  return reorderLine(map, newArray);
}

/**
 * @param input {string}
 */
function partTwo(input) {
  const [ruleMap, data] = parseInput(input);
  const inValidData = data.filter((entry) => !isValidLine(ruleMap, entry));
  // console.log(ruleMap, inValidData[0]);
  // reorderLine(ruleMap, inValidData[2]);

  const reorderedLines = inValidData.map((line) => reorderLine(ruleMap, line));
  const total = reorderedLines.reduce((acc, dataLine) => {
    const middleValue = dataLine[Math.floor(dataLine.length / 2)];
    return acc + middleValue;
  }, 0);
  return total;
}

const answerOne = partOne(file);
const answerTwo = partTwo(file);
console.log("answer one: %i", answerOne);
console.log("answer two: %i", answerTwo);
