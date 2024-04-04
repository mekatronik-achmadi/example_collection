import {print_vars} from './vars.js';
import {print_ifs,print_loops} from './ifloops.js';
import {fn_power,var_power,fn_arrow} from './funcs.js';

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

