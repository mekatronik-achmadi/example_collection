let var_str = 'Hello World';
let var_int = 10;
let var_float = 4.5;
let var_bool = true;

let var_int2str = String(15);
let var_str2int = Number('15');

// note: ` used for embed variable
function print_vars() {
    console.log(`Var ${typeof(var_int)}: ${var_int}`);
    console.log(`Var ${typeof(var_float)}: ${var_float}`);
    console.log(`Var ${typeof(var_str)}: ${var_str}`);
    console.log(`Var ${typeof(var_bool)}: ${var_bool}`);

    console.log(`Var ${typeof(var_int2str)}: ${var_int2str}`);
    console.log(`Var ${typeof(var_str2int)}: ${var_str2int}`);
}

module.exports = {
    print_vars,
};
