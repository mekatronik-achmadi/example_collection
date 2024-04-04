export class Car{
    // constructor method
    constructor(name,year){
        this.name = name;
        this.year = year;
    }

    print_car() {
        console.log(`Name: ${this.name} and Year: ${this.year}`);
    }
}
