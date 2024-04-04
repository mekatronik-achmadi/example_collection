// function declaration
export function fn_power(x = 2,y = 1) {
    return x**y;
}

//function expression
export let var_power = function(){
    return fn_power();
};

// function arrow
// '_' is just to take position argument
export let fn_arrow = (a,_) => {
    console.log(`Power Arrow: ${fn_power(a)}`);
}


