#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>

// Define pin numbers
const int gasSensorPin = 34;
const int fireSensorPin = 35;
const int ledPin = 13; 
const int servoPin = 14;
const int sprinklerPin = 12;
const int gasThreshold = 400;

// Wi-Fi and Email settings
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 587
#define sender_email "your_sender_email@gmail.com"
#define sender_password "your_email_app_password"
#define Recipient_email "recipient_email@gmail.com"
#define Recipient_name "Recipient"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gasValve;
SMTPSession smtp;

int gasValue = 0;
int fireValue = 0;
bool emailSent = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Gas Leakage");
  lcd.setCursor(0, 1);
  lcd.print("Detection & Prev");
  delay(2000);
  lcd.clear();

  pinMode(gasSensorPin, INPUT);
  pinMode(fireSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sprinklerPin, OUTPUT);

  gasValve.attach(servoPin);
  gasValve.write(0);

  digitalWrite(ledPin, LOW);
  digitalWrite(sprinklerPin, LOW);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }

  smtp.debug(1);
}

void sendEmail(String subject, String body) {
  ESP_Mail_Session session;
  session.server.host_name = SMTP_server;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;

  SMTP_Message message;
  message.sender.name = "ESP32";
  message.sender.email = sender_email;
  message.subject = subject.c_str();
  message.addRecipient(Recipient_name, Recipient_email);
  message.text.content = body.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!smtp.connect(&session)) return;

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Email send error: " + smtp.errorReason());
  }
}

void loop() {
  gasValue = analogRead(gasSensorPin);
  fireValue = analogRead(fireSensorPin);

  lcd.setCursor(0, 0);
  lcd.print("Gas Value: ");
  lcd.print(gasValue);

  if (gasValue > gasThreshold) {
    digitalWrite(ledPin, HIGH);
    gasValve.write(90);
    lcd.setCursor(0, 1);
    lcd.print("Gas Detected");

    if (!emailSent) {
      sendEmail("Gas Detected", "Warning: Gas leakage detected!");
      emailSent = true;
    }
  } else {
    digitalWrite(ledPin, LOW);
    gasValve.write(0);
    lcd.setCursor(0, 1);
    lcd.print("No Gas         ");
  }

  if (fireValue < 3000) {
    digitalWrite(sprinklerPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fire Detected");

    if (!emailSent) {
      sendEmail("Fire Detected", "Warning: Fire detected!");
      emailSent = true;
    }
  } else {
    digitalWrite(sprinklerPin, HIGH);
    lcd.print("No Fire         ");
  }

  if (gasValue <= gasThreshold && fireValue > 3000) {
    emailSent = false;
  }

  delay(1000);
}
