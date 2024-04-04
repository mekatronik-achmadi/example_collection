import {print_vars} from './vars.js';
import {print_ifs,print_loops} from './ifloops.js';
import {fn_power,var_power,fn_arrow} from './funcs.js';
import {print_array} from './array.js';
import {Car} from './class.js';

import {runserver} from './server/server.js';

console.log('NodeJS Example');

console.log('===== Variables ========');
print_vars();

console.log('====  Ifs/Loop =====');
print_ifs();
print_loops();

console.log('==== Function =====');
console.log(`Power Fn: ${fn_power(4,3)}`);
console.log(`Power Var: ${var_power()}`);
fn_arrow(4);

console.log('==== Array =====');
print_array();

console.log('==== Class =====');
let jepp = new Car('Jepp',2010);
jepp.print_car();

console.log('==== Server =====');
runserver();

