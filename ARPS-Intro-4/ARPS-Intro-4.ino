/*
 Project: Intro-4-Functions             Activity: mirobo.tech/arps-intro-4
 Date:    January 12, 2024
 
 This introductory programming activity for the mirobo.tech ARPS circuit
 demonstrates the use of functions and the ability to pass variables between
 the program's main code and the function code.
 
 Additional program analysis and programming activities examine the location of
 function code within the program, reinforce the concepts of local and global
 variables, and explore some benefits of functions.
*/

// Define I/O pins used for human interface devices
const int SW2 = 0;      // ARPS pushbuttons SW2 and SW3 are supported on
const int SW3 = 1;      // Arduino UNO R4 Minima and Arduino UNO R4 WiFi
const int SW4 = 2;      // ARPS pushbuttons SW4 and SW5 work on all
const int SW5 = 3;      // Arduino UNO R3 and Arduino UNO R4 circuit boards

const int LED2 = 5;     // ARPS top-side LEDs
const int LED3 = 6;
const int LED4 = 9;
const int LED5 = 10;

const int BEEPER = 11;  // ARPS Piezo beeper LS1
const int onboardLED = 13;  // Arduino on-board LED

// Define program constants
const int NOBUTTON = 0;
const int UP = 1;
const int DOWN = 2;
const int MAX = 3;

// Define program variables
int SW2state;
int SW3state;
int SW4state;
int SW5state;

int LED3level = 127;
int button;

void setup() {
  pinMode(onboardLED,OUTPUT);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(BEEPER,OUTPUT);
  tone(BEEPER,4000,100);  // Say hello!
}

int readButton(void) {
  SW2state = digitalRead(SW2);
  SW3state = digitalRead(SW3);
  SW4state = digitalRead(SW4);

  if(SW3state == LOW) {     // Change to SW5 for Arduino UNO R3
    return(DOWN);
  }
  else if (SW4state == LOW) {
    return(UP);
  }
  else if (SW2state == LOW) {
    return(MAX);
  }
  else {
    return(NOBUTTON);
  }
}

void setLED3Level(int btn) {
  if(btn == UP && LED3level < 255) {
    LED3level += 1;
  }

  if(btn == DOWN && LED3level > 0) {
    LED3level -= 1;
  }

  if(btn == MAX) {
    for(LED3level; LED3level != 255; LED3level ++) {
      analogWrite(LED3,LED3level);
      delay(2);
    }
  }
  analogWrite(LED3,LED3level);
}

void loop() {
  // Read buttons
  button = readButton();

  // Set LED output level
  setLED3Level(button);

  // Add a short user delay
  delay(10);
}

// Move the function code to this location in Program Analysis Activities 6.


/* Learn More -- Program Analysis Activities
 * 
 * 1.   Let's learn about functions, and how to use them in your programs.
 *      Every function begins with a function declaration - it's the first
 *      line of the function and includes the function's return type, the
 *      function name, and any optional parameters that may be required by
 *      the function. The 'void setup()' and 'void loop()' statements that
 *      have been a part of every introductory programming activity so far
 *      are actually functions declarations, and the program code inside of
 *      their braces is a part of their respective functions.
 *
 *      This program contains two new functions. The first one begins with
 *      the function declaration 'int readButton(void)'. The 'int' refers to 
 *      the type of numeric data that will be returned by this readButton()
 *      function to the statement that calls it, which allows data to be 
 *      passed from the function to the calling code. The 'void' parameter
 *      following the function's name means that this function does not
 *      accept any parameters and could have been left as empty brackets,
 *      exactly as in the setup() and loop() functions.
 *
 *      The second function's declaration is 'void setLED3Level(int btn)'.
 *      Like both the setup() and loop() functions, this function has a
 *      'void' return type, meaning that it does not return any data to the
 *      statement that called the function. This function does accept data
 *      from its calling statement though. What kind of data do you think
 *      the 'int btn' parameter defines, and what do you think this data is
 *      used for inside the function?
 * 
 * 2.   Based on your experience in the previous Intro-3-Loops activity, do
 *      you think the 'btn' variable is global, or local to the function? Why?
 * 
 * 3.   How does the 'btn' variable get assigned a value in the program? Where
 *      does this value come from?
 * 
 * 4.   Is the 'button' variable a global or local variable? How do you know?
 *
 * 5.   How does the 'button' variable get assigned a value, and in what part
 *      of the program does this take place?
 *
 * 6.   The new functions were added inbetween the existing setup() and loop() 
 *      functions and didn't seem to affect how the program runs because
 *      setup() and loop() are always the first and second functions to run,
 *      respectively. Can the new functions be moved to a different location
 *      in the program? Let's find out. Move the functions to the location
 *      shown by the comment underneath the loop() function in the prgoram.
 *      Build and upload the program. Does it still work the same way?
 *
 * 7.   Let's explore some of the advantages of using functions. Examine the
 *      loop() function in this program and imagine what it would look like
 *      if it contained the program code that has been relocated to the new,
 *      separate functions. While it does take extra effort to craft new
 *      functions for a program, can you explain any potential benefits of
 *      creating and using the two functions for this program, especially
 *      for a programmer seeing this program code for the first time?
 * 
 * 8.   Multiple parameters can be passed to a function. Add the beepBoop()
 *      function, below, to your program:
 
void beepBoop(int hiFrq, int lowFrq, int dur) {
  tone(BEEPER,hiFrq);
  delay(dur);
  tone(BEEPER,lowFrq);
  delay(dur);
  noTone(BEEPER);
}

 *      Comment-out the program code that calls both the readButton() and 
 *      setLED3Level() functions, and add the code to call beepBoop() if SW5
 *      is pressed, listed below:
 
  SW5state = digitalRead(SW5);
  if(SW5state == LOW) {
    beepBoop(1050,880,200);
  }

 *      Build and upload the program to your circuit to try it out.
 *
 * 9.   We can use the new beepBoop() function to help demonstrate another
 *      advantage of functions, namely the concept of code re-use. The
 *      existing beepBoop() function can easily be used by another part of the
 *      program. To demonstrate this, add a second button input that calls the
 *      beepBoop() function using different paramters than those used by SW5.
 * 
 * Programming Activities
 * 
 * 1.   Create a function that uses your circuit board's LEDs as a simple
 *      level gauge to display the value of a variable. Think about the range
 *      of values you would want to display, perhaps 0-100, or 0-255, for
 *      exaple. Think about how the data will be displayed. Would the LED
 *      representing the highest value only be lit for that value (e.g. if
 *      displaying a range from 0-100, would the top LED only light for 100?),
 *      or would it stay lit until a slightly lower value is reached?
 *
 *      Test your function by using two pushbuttons to increase or decrease
 *      the value of the variable, the same way the setLED3Level() function
 *      does. If you think it's worthwhile, make your pushbutton code into its
 *      own function.
 *
 * 2.   Create a function to display the binary numbers from 0-15 on the LEDs.
 *      Use the pushbuttons or a slowly changing loop to test your function.
 *
 * 3.   A function that converts an 8-bit value (0-255) into its equivalent
 *      3-digit decimal numbers might be useful for helping to debug programs
 *      or to output data to seven-segment LEDs and LCDs. Create a function that
 *      converts a number passed to it into three individual hundreds, tens, and
 *      ones digits, and stores the values in three global variables. For example,
 *      passing the function the value of 142 will result in the hundreds digit
 *      variable containing the value 1, the tens digit variable containing 4,
 *      and the ones variable 2. Test this function using the binary display
 *      function created in step 2, above.
 *
 * 4.   Create a sound effect function that sweeps between two frequencies passed
 *      to it by the calling code.
 */
