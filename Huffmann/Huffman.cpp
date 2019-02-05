#include <bits/stdc++.h> 

using namespace std; 

map<char, string> huffmanValues; // do mapowania każdego znaku na kod huffmana

// struktura reprezentująca węzeł
struct Node 
{ 
	char character;			
	int frequency;
	Node *left, *right; 

	Node(char character, int frequency) 
	{ 
		left = right = NULL; 
		this->character = character; 
		this->frequency = frequency; 
	} 
}; 

// Funkcja do porównywania wartość w lewym i prawym nodzie(odpowiednia kolejność na stercie)
struct Comparator 
{ 
	bool operator()(Node* left, Node* right) 
	{ 
		return (left->frequency > right->frequency); 
	} 
}; 

// Kolejka priorytetowa przechowująca drzewo huffmana, biorąc pod uwagę wartość roota
priority_queue<Node*, vector<Node*>, Comparator> tree; // <typ danych, kontener przechowujący dane, funktor do porównywania danych>

// Funkcja do przechowywania znaków z ich kodami huffmana
void storeHuffmanValues(struct Node* root, string text) 
{ 
	if (root == NULL) 
		return; 
		
	if (root->character != '@') 
		huffmanValues[root->character] = text; 
		
	storeHuffmanValues(root->left, text + "0"); 
	storeHuffmanValues(root->right, text + "1"); 
} 

// Funkcja budują drzewo huffmana i przechowująca go na stercie
void buildHuffmanTree(string text) 
{ 
	struct Node *left, *right, *top; 
	map<char, int> frequencies; //do przechowywania ilości wystąpień danego znaku w tekście
	
	//Tworzę mapę ilości wystąpień danego znaku w tekście
	for (int i = 0; i < text.size(); i++) 
		frequencies[text[i]]++; 
		
	for (map<char, int>::iterator it = frequencies.begin(); it != frequencies.end(); it++) 
		tree.push(new Node(it->first, it->second)); 
		
	while (tree.size() != 1) 
	{ 
		left = tree.top();
		tree.pop(); 
		right = tree.top(); 
		tree.pop(); 
		top = new Node('@', left->frequency + right->frequency); 
		top->left = left; 
		top->right = right; 
		tree.push(top); 
	} 
	
	storeHuffmanValues(tree.top(), "");
} 

// Funkcja dekodująca zakodowany tekst, przechodzi po każdym znaku w tekście, jeśli napotka 0 to idzie w lewego child'a, jeśli jeden to w prawego
// jeśli natrafi na węzeł liścia dodaje znak do wynikowego tekstu
string decodeText(struct Node* root, string text) 
{ 
	string result = ""; 
	struct Node* current = root; 
	
	for (int i = 0; i < text.size(); i++) 
	{ 
		if (text[i] == '0') 
			current = current->left; 
		else
			current = current->right; 

		// Jeśli osiągnelismy węzeł liscia -> dodaj znak do wyniku
		if (current->left == NULL and current->right == NULL) 
		{ 
			result += current->character; 
			current = root; 
		} 
	} 

	return result; 
} 

void encode(){
	ifstream file;
	string fileName = "text.txt";
	string text, encodedText;
	ofstream frequenciesFile, resultFile;
	string frequenciesFileName = "frequencies.txt";
	string resultFileName = "encoded.txt";
	
	file.open(fileName);
	getline(file, text);
	file.close();
	
	buildHuffmanTree(text);
	
	for (auto i: text) 
		encodedText += huffmanValues[i]; 
	
	frequenciesFile.open(frequenciesFileName, ios_base::app);
	for (auto it = huffmanValues.begin(); it != huffmanValues.end(); it++) 
		frequenciesFile << it->first << ": " << it->second << endl; 
	frequenciesFile.close();

	resultFile.open(resultFileName, ios_base::app);
	resultFile << encodedText;
	resultFile.close();
}

void decode(){
	ifstream file;
	string fileName = "encoded.txt";
	string text, decodedText;
	
	file.open(fileName);
	getline(file, text);
	file.close();
	
	decodedText = decodeText(tree.top(), text);
	
	ofstream resultFile;
	string resultFileName = "decoded.txt";
	
	resultFile.open(resultFileName, ios_base::app);
	resultFile << decodedText;
	resultFile.close();	
}

int main() 
{ 
  	encode();
  	
	decode();
	
	cout << "SUCCESS!!!" << endl;
	
	return 0; 
} 
