struct Merchandise {
private:
	char name[40];
	unsigned short number;
	float price;
	int sold;

public:
	Merchandise();
	Merchandise(char * name, unsigned short number, float price);
	Merchandise(const Merchandise& newElement);

	void print();

	char* getName();
	unsigned short getNumber();
	float getPrice();
	int getSold();

	void setName(char * name);
	void setNumber(unsigned short number);
	void setPrice(float price);
	void setSold(int sold);
};
