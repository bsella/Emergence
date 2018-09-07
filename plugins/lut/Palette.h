#ifndef PALETTE_H
#define PALETTE_H

class Palette{
private:
	struct color{
		color(Palette* p,unsigned c, double a);
		color(color*);
		Palette* plt;
		struct color* next=nullptr;
		struct color* prev=nullptr;
		const unsigned clr;
		double alpha;
		void updateAlpha(double newAlpha);
	};
	void remove(color* c);
	static unsigned average(color c1, color c2, double i);
	struct color*first=nullptr;
	struct color*last=nullptr;
	friend class LutCursor;
	friend class LutView;
public:
	Palette();
	Palette(const Palette&);
	~Palette();
	color* add(unsigned color, double alpha);
	unsigned operator[](double alpha)const;
	bool empty()const;
};

#endif
