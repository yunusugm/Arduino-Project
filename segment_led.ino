// ? Set arduino pin
byte segmentPin[] = {2, 3, 4, 5, 6, 7, 8, 9};

// ? Set segment LED array
int number[9][8] = {
    {1, 1, 0, 0, 0, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 0, 1, 0}, // 2
    {1, 0, 0, 0, 0, 0, 1, 0}, // 3
    {1, 1, 0, 0, 0, 1, 0, 0}, // 4
    {1, 0, 0, 0, 1, 0, 0, 0}, // 5
    {0, 0, 0, 0, 1, 0, 0, 0}, // 6
    {1, 1, 0, 0, 0, 0, 0, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0, 0}, // 8
    {1, 1, 0, 0, 0, 0, 0, 0}, // 9
};

void setup()
{
  for (byte i = 0; i < 8; i++)
  {
    pinMode(segmentPin[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      digitalWrite(segmentPin[j], number[i][j]);
    }
    delay(1000);
  }
}