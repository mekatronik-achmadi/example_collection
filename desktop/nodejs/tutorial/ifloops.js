let var_int = 9;

function print_ifs() {
    let var_mod = var_int % 2;

    if(var_mod === 0){
        console.log(`${typeof(var_int)} is even`);
    }
    else if(var_mod === 1){
        console.log(`${typeof(var_int)} is odd`);
    }
    else {
        console.log(`${typeof(var_int)} is undefined`);
    }
}

function print_loops() {
    for(let i=0;i<var_int;i++){
        process.stdout.write(`${i} `);
    }
    process.stdout.write('\n');

    let j = 0;
    while(j<var_int){
        process.stdout.write(`${j} `);
        j = j + 1;
    }
    process.stdout.write('\n');
}

module.exports = {
    print_ifs,
    print_loops,
};
