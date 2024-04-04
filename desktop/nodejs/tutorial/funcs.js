// function declaration
function fn_power(x = 2,y = 1) {
    return x**y;
}

//function expression
let var_power = function(){
    return fn_power();
};

// function arrow
// '_' is just to take position argument
let fn_arrow = (a,_) => {
    console.log(`Power Arrow: ${fn_power(a)}`);
}

module.exports = {
    fn_power,
    var_power,
    fn_arrow,
};

