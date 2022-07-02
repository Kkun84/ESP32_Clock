#include <WiFi.h>
#include <time.h>

void setup()
{
    Serial.begin(115200);
    delay(100);
    Serial.print("\n\nStart\n");

    WiFi.begin();
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(500);
    }
    Serial.println();
    Serial.printf("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    configTzTime("JST-9", "ntp.nict.jp");
    delay(5000);
}

void loop()
{
    static const char *wd[7] = {"日", "月", "火", "水", "木", "金", "土"};
    static unsigned long last_millis = 0;

    unsigned long new_millis = millis();

    time_t t;
    struct tm *tm;

    t = time(NULL);
    tm = localtime(&t);

    Serial.printf(
        "%04d/%02d/%02d(%s) %02d:%02d:%02d %lu(%lu)\n",
        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
        wd[tm->tm_wday],
        tm->tm_hour, tm->tm_min, tm->tm_sec,
        new_millis - last_millis, new_millis);

    last_millis = new_millis;
    delay(200);
}
