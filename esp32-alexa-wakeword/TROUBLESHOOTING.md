# 🔧 دليل حل المشاكل الشامل

## 📋 فهرس المشاكل

1. [مشاكل البناء (Build)](#1-مشاكل-البناء-build)
2. [مشاكل الرفع (Flash)](#2-مشاكل-الرفع-flash)
3. [مشاكل الميكروفون](#3-مشاكل-الميكروفون)
4. [مشاكل الكشف](#4-مشاكل-الكشف)
5. [مشاكل الأداء](#5-مشاكل-الأداء)
6. [مشاكل ESP-SR](#6-مشاكل-esp-sr)

---

## 1. مشاكل البناء (Build)

### ❌ خطأ: `esp-sr: No such file or directory`

**السبب:** مكتبة ESP-SR غير موجودة في `components/`

**الحل:**
```bash
cd components
git clone https://github.com/espressif/esp-sr.git
cd ..
idf.py reconfigure
idf.py build
```

---

### ❌ خطأ: `CMake Error: Could not find CMAKE_MAKE_PROGRAM`

**السبب:** أدوات البناء غير مثبتة

**الحل (Linux/Mac):**
```bash
# Ubuntu/Debian
sudo apt-get install cmake ninja-build

# macOS
brew install cmake ninja
```

**الحل (Windows):**
```powershell
# استخدم ESP-IDF installer الرسمي
# يحتوي على جميع الأدوات المطلوبة
```

---

### ❌ خطأ: `Target "esp32s3" is not supported`

**السبب:** نسخة ESP-IDF قديمة

**الحل:**
```bash
cd $IDF_PATH
git fetch
git checkout v5.1
git submodule update --init --recursive
./install.sh esp32s3
. ./export.sh
```

---

### ❌ خطأ: `undefined reference to 'i2s_channel_init_std_mode'`

**السبب:** استخدام API قديم لـ I2S

**الحل:**
```bash
# تأكد من استخدام ESP-IDF v5.0+
idf.py --version

# إذا كانت النسخة قديمة، حدّث:
cd $IDF_PATH
git checkout v5.1
./install.sh
```

---

## 2. مشاكل الرفع (Flash)

### ❌ خطأ: `Serial port not found`

**السبب:** المنفذ التسلسلي غير متصل أو غير صحيح

**الحل (Linux):**
```bash
# اعرض المنافذ المتاحة
ls /dev/ttyUSB* /dev/ttyACM*

# أضف المستخدم إلى مجموعة dialout
sudo usermod -a -G dialout $USER
# ثم أعد تسجيل الدخول

# استخدم المنفذ الصحيح
idf.py -p /dev/ttyUSB0 flash
```

**الحل (Windows):**
```powershell
# افتح Device Manager
# ابحث عن "Ports (COM & LPT)"
# ابحث عن "USB Serial Port (COMx)"

# استخدم المنفذ الصحيح
idf.py -p COM3 flash
```

**الحل (macOS):**
```bash
# اعرض المنافذ
ls /dev/cu.*

# استخدم المنفذ الصحيح
idf.py -p /dev/cu.usbserial-* flash
```

---

### ❌ خطأ: `Failed to connect to ESP32-S3`

**السبب:** اللوحة في وضع خاطئ أو كابل USB تالف

**الحل:**
```bash
# 1. اضغط مع الاستمرار على زر BOOT
# 2. اضغط على زر RESET
# 3. اترك زر RESET
# 4. اترك زر BOOT
# 5. حاول الرفع مرة أخرى

idf.py -p /dev/ttyUSB0 flash

# إذا لم ينجح، جرب:
esptool.py --chip esp32s3 --port /dev/ttyUSB0 erase_flash
idf.py -p /dev/ttyUSB0 flash
```

---

### ❌ خطأ: `A fatal error occurred: Packet content transfer stopped`

**السبب:** كابل USB رديء أو منفذ USB ضعيف

**الحل:**
```bash
# 1. جرب كابل USB آخر (يفضل قصير وجيد)
# 2. جرب منفذ USB آخر (يفضل USB 2.0)
# 3. قلل سرعة الرفع:

idf.py -p /dev/ttyUSB0 -b 115200 flash
```

---

## 3. مشاكل الميكروفون

### ❌ المشكلة: الميكروفون لا يقرأ أي صوت

**الأعراض:**
```
I (1234) WAKE_WORD: Audio energy level: 0
I (1235) WAKE_WORD: Audio energy level: 0
I (1236) WAKE_WORD: Audio energy level: 0
```

**الحلول:**

#### الحل 1: فحص التوصيلات
```bash
# تحقق من:
✓ VCC → 3.3V (ليس 5V!)
✓ GND → GND
✓ SCK → GPIO18
✓ WS  → GPIO5
✓ SD  → GPIO4
```

#### الحل 2: فحص L/R
```bash
# جرب توصيل L/R (WS) إلى:
# - GND (قناة يسرى)
# - VCC (قناة يمنى)
# - GPIO5 (التحكم البرمجي)
```

#### الحل 3: فحص الدبابيس في الكود
```c
// في main/i2s_config.h
#define I2S_BCK_PIN     18  // تأكد من التطابق
#define I2S_WS_PIN      5
#define I2S_DATA_IN_PIN 4
```

#### الحل 4: إضافة تأخير بعد التهيئة
```c
// في main/i2s_config.c، بعد i2s_channel_enable()
vTaskDelay(pdMS_TO_TICKS(100));  // انتظر 100ms
```

---

### ❌ المشكلة: الصوت مشوه أو به ضوضاء

**الحلول:**

#### الحل 1: تحسين التوصيلات
```bash
# استخدم أسلاك قصيرة (< 20cm)
# تجنب الأسلاك الطويلة أو المتشابكة
# أبعد الأسلاك عن مصادر الضوضاء (WiFi, Bluetooth)
```

#### الحل 2: إضافة مكثف تنعيم
```
VCC ──┬──► INMP441 VCC
      │
     [10µF]
      │
GND ──┴──► INMP441 GND
```

#### الحل 3: تحسين إعدادات I2S
```c
// في main/i2s_config.c
chan_cfg.dma_desc_num = 8;   // زيادة عدد buffers
chan_cfg.dma_frame_num = 512; // تقليل حجم frame
```

---

### ❌ المشكلة: قراءات الميكروفون كلها أصفار

**الحلول:**

#### الحل 1: فحص الطاقة
```bash
# استخدم multimeter
# قس الجهد على VCC: يجب أن يكون 3.3V
# إذا كان 0V = توصيلة مقطوعة
# إذا كان 5V = خطر! افصل فورًا
```

#### الحل 2: فحص INMP441
```bash
# قد يكون INMP441 تالفًا
# جرب INMP441 آخر إذا كان متاحًا
```

#### الحل 3: تبديل الدبابيس
```c
// جرب دبابيس I2S مختلفة
#define I2S_BCK_PIN     16
#define I2S_WS_PIN      17
#define I2S_DATA_IN_PIN 15
```

---

## 4. مشاكل الكشف

### ❌ المشكلة: لا يكتشف كلمة "Alexa"

**الأعراض:**
```
I (1234) MAIN: System running... Listening for 'Alexa'
I (6234) MAIN: System running... Listening for 'Alexa'
# لا توجد رسالة كشف
```

**الحلول:**

#### الحل 1: تحقق من مستوى الصوت
```bash
# في المونيتور، ابحث عن:
I (1234) WAKE_WORD: Audio energy level: 12345

# إذا كان الرقم صغير جدًا (< 1000):
# - تكلم بصوت أعلى
# - قرّب الميكروفون
# - قلل الضوضاء المحيطة
```

#### الحل 2: اضبط threshold
```c
// في main/wake_word_detector.c
if (energy > 500000) {  // قلل الرقم لحساسية أعلى
    // كشف
}
```

#### الحل 3: استخدم ESP-SR الحقيقي
```bash
# الكاشف الحالي بسيط (يعتمد على الطاقة فقط)
# للكشف الحقيقي، أضف ESP-SR:

cd components
git clone https://github.com/espressif/esp-sr.git
cd ..

# ثم فعّل الكود في wake_word_detector.c
```

---

### ❌ المشكلة: كشف خاطئ (False Positives)

**الأعراض:**
```
# يكتشف "Alexa" عند أي صوت عالٍ
I (1234) WAKE_WORD: ⚠️  SIMULATED WAKE WORD DETECTED
```

**الحلول:**

#### الحل 1: زيادة threshold
```c
// في main/wake_word_detector.c
if (energy > 2000000) {  // زيادة الرقم لحساسية أقل
    // كشف
}
```

#### الحل 2: إضافة debouncing
```c
// في main/wake_word_detector.c
static uint32_t last_detection = 0;
uint32_t now = xTaskGetTickCount() * portTICK_PERIOD_MS;

// لا تكشف إلا مرة كل 5 ثواني
if (now - last_detection > 5000) {
    last_detection = now;
    // كشف
}
```

#### الحل 3: استخدم ESP-SR
```bash
# ESP-SR يستخدم نماذج تعلم آلي متقدمة
# دقة أعلى بكثير من الكاشف البسيط
```

---

## 5. مشاكل الأداء

### ❌ المشكلة: `Task watchdog got triggered`

**السبب:** المعالج مشغول جدًا

**الحل:**
```c
// في main/main.c، في audio_processing_task()
while (1) {
    // ... معالجة الصوت ...
    
    // أضف تأخير صغير
    vTaskDelay(pdMS_TO_TICKS(10));  // 10ms
}
```

---

### ❌ المشكلة: الذاكرة ممتلئة

**الأعراض:**
```
E (1234) MAIN: Failed to allocate memory
E (1235) heap: alloc failed
```

**الحل:**
```bash
# في menuconfig
idf.py menuconfig

# اذهب إلى:
# Component config → ESP32S3-Specific → Support for external PSRAM
# اختر: Enable

# ثم:
# Component config → ESP32S3-Specific → SPI RAM config
# اختر: Integrate RAM into memory map
```

---

### ❌ المشكلة: بطء في الاستجابة

**الحل:**
```c
// قلل حجم buffer
#define I2S_READ_LEN (512)  // بدلاً من 1024

// زيادة أولوية المهمة
xTaskCreate(audio_processing_task, "audio_task", 4096, NULL, 10, NULL);
//                                                            ↑ زيادة من 5 إلى 10
```

---

## 6. مشاكل ESP-SR

### ❌ خطأ: `esp_wn_iface.h: No such file`

**السبب:** ESP-SR غير مثبت بشكل صحيح

**الحل:**
```bash
cd components
rm -rf esp-sr  # احذف النسخة القديمة
git clone --recursive https://github.com/espressif/esp-sr.git
cd ..
idf.py reconfigure
idf.py build
```

---

### ❌ خطأ: `Model file not found`

**الحل:**
```bash
# تأكد من وجود ملفات الموديل
ls components/esp-sr/model/

# إذا كانت فارغة:
cd components/esp-sr
git submodule update --init --recursive
```

---

### ❌ خطأ: `WakeNet initialization failed`

**الحل:**
```bash
# في menuconfig
idf.py menuconfig

# اذهب إلى:
# Component config → ESP Speech Recognition
# - اختر WakeNet model المناسب
# - تأكد من تفعيل "Alexa" wake word
```

---

## 🔍 أدوات التشخيص

### أداة 1: فحص I2S

```c
// أضف في main/main.c
void test_i2s_read(void) {
    int16_t buffer[128];
    size_t bytes_read;
    
    for (int i = 0; i < 10; i++) {
        i2s_read_audio(buffer, sizeof(buffer), &bytes_read);
        
        ESP_LOGI("TEST", "Read %d bytes", bytes_read);
        ESP_LOGI("TEST", "First sample: %d", buffer[0]);
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
```

### أداة 2: فحص الذاكرة

```c
// أضف في main/main.c
void print_memory_info(void) {
    ESP_LOGI("MEM", "Free heap: %lu bytes", esp_get_free_heap_size());
    ESP_LOGI("MEM", "Min free heap: %lu bytes", esp_get_minimum_free_heap_size());
    ESP_LOGI("MEM", "Largest free block: %lu bytes", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
}
```

### أداة 3: فحص GPIO

```bash
# في المونيتور، استخدم أوامر:
# (يتطلب تفعيل console في menuconfig)

gpio_dump
# يعرض حالة جميع GPIO
```

---

## 📞 الحصول على المساعدة

إذا لم تحل المشكلة:

1. **جمع المعلومات:**
   ```bash
   # احفظ لوجات المونيتور
   idf.py monitor > logs.txt
   
   # احفظ معلومات النظام
   idf.py --version > system_info.txt
   uname -a >> system_info.txt
   ```

2. **افتح Issue على GitHub:**
   - أرفق `logs.txt`
   - أرفق `system_info.txt`
   - اشرح المشكلة بالتفصيل
   - أرفق صور للتوصيلات

3. **انضم إلى المجتمع:**
   - [ESP32 Forum](https://esp32.com/)
   - [ESP-IDF GitHub Discussions](https://github.com/espressif/esp-idf/discussions)
   - [Reddit r/esp32](https://reddit.com/r/esp32)

---

**نصيحة:** احتفظ بهذا الملف مرجعًا سريعًا! معظم المشاكل لها حلول بسيطة. 🔧✨
