#include <iostream>

using namespace std;

class Kotak{
public:
    Kotak(int p, int l, int t, const char* c, int w){
        panjang = p;
        lebar = l;
        tinggi = t;
        ubah_warna(c);
        berat = w;
    }
    int hitung_volume(){
        return panjang*lebar*tinggi;
    }
    void ubah_warna(const char *c){
        int i = 0;
        while(*c){
            warna[i] = *c++;
            i++;
        }
        warna[i] = '\0';
    }
    char *get_warna(){
        return warna;
    }
private:
    int panjang;
    int lebar;
    int tinggi;
    char warna[12];
    int berat;
};
typedef enum{
    OFF=0,
    ON=1
}status_t;

class LED{
public:
    LED(const char *wrn, status_t sts){
        int i = 0;
        while(*wrn){
            warna[i] = *wrn++;
            i++;
        }
        status = sts;
    }
    void On(){

    }

private:
    char warna[10];
    status_t status;
};

class CasingCPU : public Kotak
{
public:
	CasingCPU(int p, int l, int t,
				const char* c, int w,
				bool ps, const char *mrk)
		: Kotak(p,l,t,c,w)
	{
		ada_power_supply = ps;
		int i= 0;
		while(*mrk){
			merek[i] = *mrk++;
			i++;
		}
        merek[i] = '\0';

        LED LedPower("hijau",OFF);
        pLedPower = &LedPower;
        LED LedHardisk("oranye",OFF);
        pLedHardisk = &LedHardisk;
	}
	void LedPowerOn(){
        pLedPower->On();
	}
private:
	bool ada_power_supply;
	char merek[15];
	LED *pLedPower;
	LED *pLedHardisk;
};

int main()
{
    int volume;
    Kotak peti(10,20,30,"merah",40);

    volume = peti.hitung_volume();
    cout << "volume = "<< volume << endl;
    cout << "warna = "<< peti.get_warna() << endl;
    peti.ubah_warna("biru");
    cout << "warna baru= "<< peti.get_warna() << endl;

    CasingCPU CPU102(10,20,30,"abu-abu",1,false,"thunder bird");
    CasingCPU CPU103(10,20,30,"putih",1,false,"thunder bird");
    CasingCPU CPU104(10,20,30,"biru",1,true,"thunder bird");

    volume = CPU102.hitung_volume();
    CPU103.ubah_warna("merah");
    CPU103.LedPowerOn();


    return 0;
}
