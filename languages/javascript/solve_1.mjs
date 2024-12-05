import { readFileSync } from "fs";

const file = readFileSync(
  "/home/marcus/Documents/coding/advent-of-code/2024/inputs/1.txt",
  { encoding: "utf-8" },
);

function parseInput(input) {
  return input
    .split("\n")
    .filter(Boolean)
    .map((vals) => vals.split("  ").filter(Boolean))
    .map((vals) => vals.map((val) => parseInt(val, 10)))
    .reduce(
      (acc, [one, two]) => {
        acc[0].push(one);
        acc[1].push(two);
        return acc;
      },
      [[], []],
    );
}

function partOne(listOne, listTwo) {
  [listOne, listTwo].map((list) => {
    list.sort((a, b) => a - b);
    return list;
  });
  let difference = 0;
  listOne.forEach((listOneEntry, index) => {
    const listTwoEntry = listTwo[index];
    difference += Math.abs(listOneEntry - listTwoEntry);
  });
    return difference;
}

/**
    * @param {number[]} listOne 
    * @param {number[]} listTwo 
    */
function partTwo(listOne, listTwo) {
    const countMap = new Map();
    listTwo.forEach((num)=>{
        const current = countMap.get(num) ?? 0;
        countMap.set(num, current+1);
    })
    return listOne.reduce((acc,num)=>acc + num * (countMap.get(num) ?? 0),0);
}

const [listOne, listTwo] = parseInput(file);
const answerOne = partOne(listOne, listTwo);
const answerTwo = partTwo(listOne,listTwo);
console.log({answerOne, answerTwo})
