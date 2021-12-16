#include <iostream>

typedef struct TNode{
    int data;
    TNode *next;
    TNode *prev;
} TNode;

class ListOperator{
    private:
	TNode *head=NULL;

    public:
	ListOperator();
	int  IsEmpty();
	void InsertDepan(int value);
	void InsertBelakang(int value);
	void HapusDepan();
	void HapusBelakang();
	void HapusSemua();
	void Tampil();
};

int main(){
	
    int data;
    int key = 0;
    int loop = 1;

    ListOperator *lo;
    lo = new ListOperator();

    do{
	std::cout << std::endl;
	std::cout << "____MENU PROGRAM____" << std::endl;
	std::cout << "[0] Keluar Program" << std::endl;
	std::cout << "[1] Insert Depan" << std::endl;
	std::cout << "[2] Insert Belakang" << std::endl;
	std::cout << "[3] Hapus Depan" << std::endl;
	std::cout << "[4] Hapus Belakang" << std::endl;
	std::cout << "[5] Hapus Semua List" << std::endl;
	std::cout << "[6] Lihat Semua List" << std::endl;
	std::cout << std::endl;
	std::cout << "Pilihan Anda [0-6] --> ";
	std::cin >> key;

	switch(key){
	    case 0:
		std::cout << "Program Keluar" << std::endl;
		loop = 0;
		break;

	    case 1:
		std::cout << "Masukkan Data : ";
		std::cin >> data;
		lo->InsertDepan(data);
		break;

	    case 2:
		std::cout << "Masukkan Data : ";
		std::cin >> data;
		lo->InsertBelakang(data);
		break;

	    case 3:
		lo->HapusDepan();
		lo->Tampil();
		break;

	    case 4:
		lo->HapusBelakang();
		lo->Tampil();
		break;

	    case 5:
		lo->HapusSemua();
		std::cout << "Seluruh data dihapus" << std::endl;
		break;

	    case 6:
		std::cout << "Menampilkan Data : " << std::endl;
		lo->Tampil();
		break;

	    default:
		std::cout << "Pilihan anda tidak berlaku" << std::endl;
		std::cout << std::endl;
		loop = 1;
			
	}

    }while(loop);

    return 0;
}

ListOperator::ListOperator(){
    head = NULL;
}

int ListOperator::IsEmpty(){
    if(head==NULL){
	return 1;
    }
    else{
	return 0;
    }
}

void ListOperator::InsertDepan(int value){
    TNode *baru;
    baru = new TNode;

    baru->data = value;
    baru->next = NULL;
    baru->prev = NULL;

    if(IsEmpty()==1){
	head = baru;
	head->next = NULL;
	head->prev = NULL;
    }
    else{
	baru->next = head;
	head->prev = baru;
	head = baru;
    }

    std::cout << "Data Masuk --> " << std::endl;
    std::cout << std::endl;
}

void ListOperator::InsertBelakang(int value){
    TNode *baru, *bantu;
    baru = new TNode;

    baru->data = value;
    baru->next = NULL;
    baru->prev = NULL;

    if(IsEmpty()==1){
	head = baru;
	head->next = NULL;
	head->prev = NULL;
    }
    else{
	bantu = head;
	while(bantu->next != NULL){
	    bantu = bantu->next;
	}
	bantu->next = baru;
	baru->prev = bantu;
    }

    std::cout << "Data Masuk --> " << std::endl;
    std::cout << std::endl;
}

void ListOperator::HapusDepan(){
    TNode *hapus;
    int dat;

    if(IsEmpty()==0){
	if(head->next != NULL){
	    hapus = head;
	    dat = hapus->data;
	    head = head->next;
	    head->prev = NULL;
	    delete hapus;
	}
	else{
	    dat = head->data;
	    head = NULL;
	}

	std::cout << dat << " Terhapus -->" << std::endl;
	std::cout << "List Baru:" << std::endl;
    }
    else{
	std::cout << "Data Kosong" << std::endl;
    }
}

void ListOperator::HapusBelakang(){
    TNode *hapus,*bantu;
    int dat;

    if(IsEmpty()==0){
	if(head->next != NULL){
	    bantu = head;
	    while(bantu->next->next != NULL){
		bantu = bantu->next;
	    }
	    hapus = bantu->next;
	    dat = hapus->data;
	    bantu->next = NULL;
	    delete hapus;
	}
	else{
	    dat = head->data;
	    head = NULL;
	}

	std::cout << dat << " Terhapus -->" << std::endl;
	std::cout << "List Baru:" << std::endl;
    }
    else{
	std::cout << "Data Kosong" << std::endl;
    }
}

void ListOperator::HapusSemua(){
    TNode *bantu, *hapus;

    bantu = head;
    while(bantu != NULL){
	hapus = bantu;
	bantu = bantu->next;
	delete hapus;
    }
    head = NULL;

    std::cout << "Semua Terhapus -->" << std::endl;
}

void ListOperator::Tampil(){
    TNode *bantu;
    bantu = head;

    if(IsEmpty()==0){
	while(bantu != NULL){
	    std::cout << bantu->data << " ";
	    bantu = bantu->next;
	}
    }
    else{
	std::cout << "Data Kosong" << std::endl;
    }
    
    std::cout << std::endl;
}
