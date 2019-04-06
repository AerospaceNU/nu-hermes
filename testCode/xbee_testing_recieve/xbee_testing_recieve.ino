void setup() {
  // put your setup code here, to run once:
  Serial3.begin(9600);
  String data;
}

void loop() {
  // put your main code here, to run repeatedly:

  data = Serial3.read();
  Serial3.println(data);
}
