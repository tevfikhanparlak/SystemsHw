# Derleyici
CC = gcc
CFLAGS = -Wall -g

# Hedef
TARGET = Game.exe

# Kaynak Dosyaları
SRCS = Game.c

# Nesne Dosyaları
OBJS = $(SRCS:.c=.o)

# Veri Dosyası
DATA_FILE = savegame.dat

# Varsayılan Hedef: Programı derle
all: $(TARGET) $(DATA_FILE)

# Programı derlemek
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# .c dosyasından .o dosyasına derlemek
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Temizlik
clean:
	del /f $(OBJS) $(TARGET)

# savegame.dat dosyasını kontrol et ve oluştur
$(DATA_FILE):
	@echo "savegame.dat dosyası oluşturuluyor..."
	@echo "Veriler burada." > $(DATA_FILE)
	@echo "savegame.dat oluşturuldu."

# savegame.dat dosyasını silmek
clean_data:
	del /f $(DATA_FILE)
	@echo "savegame.dat silindi."
