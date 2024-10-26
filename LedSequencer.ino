#define L1 2
#define L2 3
#define L3 4
#define L4 5

struct Frame{
  bool Led1;
  bool Led2;
  bool Led3;
  bool Led4;

  Frame(bool led1, bool led2, bool led3, bool led4){
    Led1 = led1;
    Led2 = led2;
    Led3 = led3;
    Led4 = led4;
  }
};

class Sequence{
  const Frame* framesArray;
  short framesArrayCount;
  
  public: 
    Sequence(const Frame* arr, short count){
      framesArray = arr;
      framesArrayCount = count;
    }
    
    // put in loop function!!
    void Run(short crossFrameDelay, short repetationDelay) const {
      for(int i = 0; i < framesArrayCount; i++){
        const Frame& currentFrame = framesArray[i]; // get the current frame REFERENCE, not copy.
  
        digitalWrite(L1, currentFrame.Led1 ? HIGH : LOW); // ternary operator
        digitalWrite(L2, currentFrame.Led2 ? HIGH : LOW);
        digitalWrite(L3, currentFrame.Led3 ? HIGH : LOW);
        digitalWrite(L4, currentFrame.Led4 ? HIGH : LOW);
  
        
        delay(crossFrameDelay);
      }
  
      delay(repetationDelay); // Note: repetationDelay is accumulated on top of crossFrameDelay after the last frame is executed.
    }
};

// Since frames and sequence is needed in the whole duration of the program, they are declared in the stack memory. no need to free them.

Frame frames[] = 
{
  Frame(true, false, true, false),
  Frame(false, true, false, true)
};

Sequence sequence(frames, sizeof(frames) / sizeof(Frame));

void setup() {
  // put your setup code here, to run once:
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sequence.Run(500, 1000);
}
