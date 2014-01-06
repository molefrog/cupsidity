var cups = require("../index.js");

console.log("Printers:");
console.log(cups.getDests());

console.log("Default:", cups.getDefault());


console.log("Print jobs:");
console.log(cups.getJobs());

// console.log(cups.printFile({
// 	title : 'testprint',
// 	dest : cups.getDefault(),
// 	filename : '/Users/molefrog/Desktop/ad2l43ZJtKM.jpg',
// 	options : {
// 		media : "Postcard(4x6in)"
// 	}
// }));