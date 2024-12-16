# Dungeon Adventure Game

Bu, oyuncunun farklı odaları keşfettiği, yaratıklara saldırdığı, eşyaları topladığı ve kendini iyileştirdiği metin tabanlı bir macera oyunudur. Oyunda, oyuncunun hayatta kalması, yaratıkları alt etmesi ve macerayı tamamlaması amaçlanır. Oyun, basit bir komut satırı arayüzü kullanır ve C dilinde yazılmıştır.

---

## Özellikler

- **Oyunu Başlatma**: Oyuncu, odalar, yaratıklar ve itemler structların yardımıyla oluşturulur ve ilk değerleri verilir.
- **Handle Command**: Kullanıcıdan input alınarak yapılmak istenen eylemi alan komut menüsü yazılır.
- **Move Player**: Oyuncu, birbirine initGame metotunda bağlanan odalar arasında right, left, up, down şeklinde hareket edebilir.
- **Look Room**: Oyuncu, odada hangi eşyaların ve varsa hangi canavarın olduğuna lookRoom metotuya bakabilir. Yapması gereken hamleyi look metotuna göre ayarlayabilir.
- **Eşyaları Toplama**: Oyuncu, odadaki eşyaları alabilir. Bu eşyalar arasında sağlık iksirleri, silahlar ve diğer faydalı nesneler bulunur.
- **Yaratıklara Saldırma**: Oyuncu, odada bulunan yaratıklara saldırabilir. Saldırılar için eşyalar veya çıplak eller kullanılabilir.
- **Oyuncuyu İyileştirme**: Oyuncu, envanterinde bulunan sağlık eşyalarını kullanarak sağlık puanlarını yenileyebilir.
- **Envanter Sistemi**: Oyuncunun taşıyabileceği sınırlı sayıda eşya vardır. Bu eşyalar saldırı, savunma veya iyileşme için kullanılabilir. Buna ek olarak kendi envanterine eklediği itemleri listeleyebilir.
- **Oyunu Kaydetme ve Yükleme**: Oyuncunun ilerlemesi bir dosyaya kaydedilebilir ve daha sonra kaldığı yerden devam edebilir.
- **Kazanç ve Kaybetme Durumları**: Oyuncu, oyundaki tüm yaratıkları öldürerek oyunu kazanabilir. Sağlık puanları sıfıra düştüğünde oyun kaybedilir.

---

## Oyunu Başlatma

### Oyunu Başlatma:
** `initGame` Metodu**  
Oyun dünyasının temel yapılarını ve başlama koşullarını hazırlar. Bu metot, odaları oluşturur, odaların bağlantılarını tanımlar, yaratıkları ve eşyaları yerleştirir. Ayrıca oyuncunun başlangıç odasını ve durumunu belirler.

- **Ne Yapar?**
  - Odaları oluşturur ve bunları birbiriyle bağlar.
  - Yaratıkları ve eşyaları rastgele odalara yerleştirir.
  - Oyuncunun başlangıç durumunu (sağlık, envanter, başlangıç odası) ayarlar.

- **Önemli Noktalar:**
  - Oyun başlangıç ayarlarının doğru olması, ilerleyen bölümlerde doğru bir oynanış için gereklidir.
  - Yaratıklar ve eşyalar her oyun başlangıcında farklı odalara yerleştirilerek oynanışı çeşitlendirir.

---

## HandleCommand

### Komutları Yönetme:
** `handleCommand` Metodu**  
Oyuncunun oyun sırasında girdiği komutları işler ve ilgili işlemleri tetikler. Tüm oyun içi etkileşimlerin merkezi bu metod üzerinden sağlanır.

- **Ne Yapar?**
  - Girilen komutu analiz eder (örneğin: `move`, `pickup`, `attack`).
  - Komuta uygun metotları çağırır (örneğin: `movePlayer`, `pickupItem`, `lookRoom`).

- **Önemli Noktalar:**
  - Komutlar doğru bir şekilde tanımlanmalıdır. Geçersiz komutlar, oyuncuya açıklayıcı bir hata mesajıyla iletilir.
  - Tüm komutlar `handleCommand` metodu içinde bir koşul yapısı ile kontrol edilir.

---
## Oynanış

###  Hareket Ettirme:
**`movePlayer` Metodu**  
Oyuncunun odalar arasında hareket etmesini sağlar. Hangi yönlere gidilebileceği kontrol edilir ve oyuncunun konumu güncellenir.

- **Ne Yapar?**
  - Oyuncunun mevcut odasını kontrol eder.
  - Hedef yönün geçerli olup olmadığını belirler (örneğin: "up", "down", "left", "right").
  - Eğer geçerli bir yön varsa oyuncuyu o yöne taşır, aksi takdirde oyuncuya hata mesajı verir.

- **Önemli Noktalar:**
  - Her oda yalnızca belirli yönlere bağlıdır. Örneğin, bir odanın yukarısında başka bir oda olmayabilir.
  - Oyuncu her hareket ettiğinde, yeni odadaki durum (eşya ve yaratıklar) kontrol edilir.

---

## Odaya Bakma

### Odaya Bakma:
**`lookRoom` Metodu**  
Oyuncunun bulunduğu odanın durumunu incelemesini sağlar. Bu metot, odada bulunan yaratıkları, eşyaları ve odanın genel tanımını oyuncuya bildirir.

- **Ne Yapar?**
  - Odadaki yaratığın ismini(varsa) ve durumlarını listeler.
  - Odadaki eşyaların isimlerini listeler.
 
- **Önemli Noktalar:**
  - Oyuncunun strateji geliştirebilmesi için odanın durumu hakkında detaylı bilgi verilmesi önemlidir.
  - Odadaki yaratıklar ve eşyalar, oyuncunun bir sonraki hareketini etkiler.

---



### **Eşya Toplama**  
Oyuncu, odalarda bulduğu faydalı eşyaları alarak envanterine ekleyebilir. Bu eşyalar, oyun sırasında ilerlemek veya hayatta kalmak için kritik öneme sahiptir.  
- **Nasıl Çalışır?**
  - Oyuncu `pickupItem` komutunu yazar.
  - Odanın envanteri kontrol edilir ve mevcut eşyalar listelenir.
  - Oyuncu seçtiği eşyayı alır ve bu eşya oyuncunun envanterine eklenir.
  - Eğer envanter doluysa, oyuncuya uyarı verilir.
- **Önemli Noktalar:**
  - Eşyaların türleri: Silahlar, sağlık iksirleri ve görev eşyaları.
  - Oyuncunun envanteri sınırlıdır; stratejik seçimler yapılmalıdır.
  - Bazı eşyalar yalnızca odadaki yaratıklar etkisiz hale getirildikten sonra toplanabilir.

---

### **Yaratıklara Saldırma**  
Odada bulunan düşman yaratıklara saldırarak oyuncu, odadaki tehlikeleri ortadan kaldırabilir. Saldırı için oyuncunun elindeki eşyalar veya çıplak eller kullanılabilir.  
- **Nasıl Çalışır?**
  - Oyuncu `attackCreature` komutunu yazar.
  - Odanın yaratığı ekrana yazdırılır.
  - Oyuncu saldırmak istediği yaratığı ve kullanmak istediği eşyayı seçer.
  - Eşyaların saldırı gücü, yaratığın sağlık puanını düşürür. Eğer yaratığın sağlık puanı sıfıra düşerse yaratık ölür.
- **Önemli Noktalar:**
  - Eşyaların saldırı gücü farklıdır. Örneğin, bir kılıç çıplak ele göre daha fazla hasar verir.
  - Eğer oyuncunun saldırı gücü düşükse yaratıklar oyuncuyu öldürebilir. Burada mantıklı item seçmek önemlidir.
  

---

### **Oyuncuyu İyileştirme**  
Oyuncu, savaş sırasında veya sonrasında sağlık eşyalarını kullanarak sağlık puanlarını yenileyebilir. Bu, oyuncunun hayatta kalması için kritik öneme sahiptir.  
- **Nasıl Çalışır?**
  - Oyuncu `healPlayer` komutunu yazar.
  - Envanterdeki sağlık eşyaları listelenir.
  - Oyuncu, kullanmak istediği sağlık eşyasını seçer.
  - Seçilen eşya kullanıldıktan sonra oyuncunun sağlık puanları yenilenir ve eşya envanterden silinir.
- **Önemli Noktalar:**
  - Sağlık eşyaları sınırlıdır; dikkatli kullanılmalıdır.
  - Bir canavarı öldürdükten sonra maksimum 2 adet kullanılabiir. 
  - İyileştirme yalnızca sağlık puanları tam dolmadığında yapılabilir.
  - Eğer sağlık eşyası yoksa oyuncuya uyarı verilir.

---

### **Envanter Sistemi**  
Oyuncunun topladığı tüm eşyalar envanterde saklanır. Envanter, sınırlı bir kapasiteye sahiptir, bu nedenle oyuncu yalnızca belirli sayıda eşya taşıyabilir.  
- **Nasıl Çalışır?**
  - Oyuncu `displayInventory` komutunu yazar.
  - Mevcut envanterdeki eşyaların isimleri ve türleri ekrana yazdırılır.
  - Oyuncu envanterdeki eşyaları kullanabilir.
  - Sağlık eşyaları kullanıldığında envanterden atılır. Bu da envanterde yer açılmasını sağlar.
- **Önemli Noktalar:**
  - Envanterdeki eşyaların doğru bir şekilde yönetilmesi gerekir.
  - Oyuncu eşyaları boş yere almamamalı çünkü envanterden sadece sağlık itemi atılır. Saldırı 
  itemleri envanterden atılmaz.
 

---

### **Kaydetme ve Yükleme**  
Oyun ilerlemesini kaydetme ve kaldığınız yerden devam etme imkanı sunar. Bu özellik, özellikle uzun oynanışlar için kullanışlıdır.  
- **Nasıl Çalışır?**
  - Oyuncu `saveGame` komutunu yazar. Oyun durumu, `savegame.dat` adlı bir dosyaya kaydedilir.
  - Oyuncu daha sonra `loadGame` komutunu yazarak oyunu kaldığı yerden devam ettirebilir.
- **Önemli Noktalar:**
  - Kaydetme işlemi sırasında, oyuncunun mevcut odası, envanteri ve sağlık durumu kaydedilir.
  - Yükleme işlemi, oyuncunun oyun durumunu tam olarak geri getirir.
  - Eğer yükleme sırasında dosya bulunamazsa, oyuncuya hata mesajı verilir.


## Gereksinimler

- C Derleyicisi (GCC veya başka bir C derleyicisi).
- Terminal veya komut satırı arayüzü.

---

## Derleme

Oyunu derlemek için aşağıdaki komutu kullanabilirsiniz:

```bash
gcc -o dungeon_adventure_game main.c
