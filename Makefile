CXX = g++
BOOST_VERSION = 1.90.0
BOOST_VERSION_UNDERSCORE = 1_90_0
BOOST_DIR = boost_$(BOOST_VERSION_UNDERSCORE)
BOOST_ARCHIVE = $(BOOST_DIR).tar.gz
BOOST_URL = https://archives.boost.io/release/$(BOOST_VERSION)/source/$(BOOST_ARCHIVE)

CXXFLAGS = -Wall -O3 -std=c++23 -I./$(BOOST_DIR)
TARGET = bench
SRC = bench.cpp

all: $(TARGET)

$(TARGET): $(SRC) $(BOOST_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Download and extract Boost
$(BOOST_DIR):
	@echo "Downloading Boost $(BOOST_VERSION)..."
	curl -L $(BOOST_URL) -o $(BOOST_ARCHIVE)
	@echo "Extracting Boost..."
	tar xzf $(BOOST_ARCHIVE)
	rm $(BOOST_ARCHIVE)
	@echo "Boost $(BOOST_VERSION) is ready!"

clean:
	rm -f $(TARGET)

clean-all: clean
	rm -rf $(BOOST_DIR)

.PHONY: all clean clean-all
