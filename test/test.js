var cups = require("../index.js");


var Table = require('cli-table');


var printers = cups.getDests();

var printersTable = new Table({
    head: [ "Name", "Model", "Default"]
});

printers.forEach(function (printer) {
	printersTable.push([
		 printer.name,
		 printer.options['printer-make-and-model'],
		 printer.is_default
	]);
});

console.log("Installed Printers:");
console.log(printersTable.toString());


var jobs = cups.getJobs({
	dest : cups.getDefault(),
	mine : false
});

var jobsTable = new Table({
    head: [ "ID", "Title", "Size", "User", "State" ]
});

jobs.forEach(function(job) {
	jobsTable.push([
		job.id,
		job.title,
		job.size,
		job.user,
		job.state
	]);
})

console.log(cups.getDefault(), "Jobs:");
console.log(jobsTable.toString());

// console.log(cups.printFile({
// 	title : 'testprint',
// 	dest : cups.getDefault(),
// 	filename : '/Users/molefrog/Desktop/ad2l43ZJtKM.jpg',
// 	options : {
// 		media : "Postcard(4x6in)"
// 	}
// }));
