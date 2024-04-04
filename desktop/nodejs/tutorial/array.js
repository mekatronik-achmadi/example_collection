let var_array =  [0, 1, 2, 3, 4];
let var_newarra = new Array(0, 2, 4, 6, 8);

function print_array() {
    for(let i=0;i<var_array.length;i++){
        process.stdout.write(`${var_array[i]} `);
    }
    process.stdout.write('\n');

    for(let i=0;i<var_newarra.length;i++){
        process.stdout.write(`${var_newarra[i]} `);
    }
    process.stdout.write('\n');
}

module.exports = {
    print_array,
}
