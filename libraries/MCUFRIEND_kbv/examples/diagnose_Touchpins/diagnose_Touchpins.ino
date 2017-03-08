void showpins(int A, int D, int value, const char *msg)
{
    Serial.print(msg);
    Serial.print(" (A" + String(A - A0) + ", D" + String(D) + ") = ");
    Serial.println(value);
}
void setup()
{
    int i, j, value, Apins[2], Dpins[2], Values[2], found = 0;
    Serial.begin(9600);
    Serial.println("Making all control and bus pins INPUT_PULLUP");
    Serial.println("Typical 30k Analog pullup with corresponding pin");
    Serial.println("would read low when digital is written LOW");
    Serial.println("e.g. reads ~25 for 300R X direction");
    Serial.println("e.g. reads ~30 for 500R Y direction");
    Serial.println("");
    for (i = A0; i < A5; i++) pinMode(i, INPUT_PULLUP);
    for (i = 2; i < 10; i++) pinMode(i, INPUT_PULLUP);
    for (i = A0; i < A4; i++) {
        for (j = 5; j < 10; j++) {
            pinMode(j, OUTPUT);
            digitalWrite(j, LOW);
            value = analogRead(i);   // ignore first reading
            value = analogRead(i);
            if (value < 100) {
                showpins(i, j, value, "Testing :");
                if (found < 2) {
                    Apins[found] = i;
                    Dpins[found] = j;
                    Values[found] = value;
                    found++;
                }
            }
            pinMode(j, INPUT_PULLUP);
        }
    }
    if (found == 2) {
        Serial.println("Diagnosing as:-");
        for (i = 0; i < 2; i++) {
            showpins(Apins[i], Dpins[i], Values[i], (Values[i] < Values[!i]) ? "XM,XP: " : "YP,YM: ");
        }
    }
}

void loop()
{
    // put your main code here, to run repeatedly:

}
