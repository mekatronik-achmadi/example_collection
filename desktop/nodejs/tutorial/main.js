let Var = require('./vars');
let IfLoop = require('./ifloops');
let Func = require('./funcs');
let Arrs = require('./array');
let Clss = require('./class');
let Srv = require('./serve');

console.log(`NodeJS ${process.version}`);

console.log('===== Variables ========');
Var.print_vars();

console.log('====  Ifs/Loop =====');
IfLoop.print_ifs();
IfLoop.print_loops();

console.log('==== Function =====');
console.log(`Power Fn: ${Func.fn_power(4,3)}`);
console.log(`Power Var: ${Func.var_power()}`);
Func.fn_arrow(4);

console.log('==== Array =====');
Arrs.print_array();

console.log('==== Class =====');
let jepp = new Clss.Car('Jepp',2010);
jepp.print_car();

console.log('==== Server =====');
console.log(`localhost:${Srv.port}`);
Srv.runserver();

