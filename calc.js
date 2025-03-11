process.stdin.on('data', (chuck) => {
    const input = chuck.toString().trim();
    if(input === 'quit') {
        process.exit(0);
    }

    try{
        const value = eval(input);
        console.log(`${value}`);
    } catch (exception){
        console.log('Invalid input');
    }

    process.stdout.write('Enter your simple equation: ');
    
});


process.stdout.write('Enter your simple equation: ');
