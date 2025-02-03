//----------İKİLİ AĞAÇ OLUŞTURMA----------
#include <stdio.h>
#include <stdlib.h> // malloc kullanımı için gerekli kütüphane

struct node
{
    int data;           // Düğümün tuttuğu veri
    struct node *left;  // Sol çocuğa işaretçi
    struct node *right; // Sağ çocuğa işaretçi
};

struct node *newNode(int x)
{
    struct node *yeni = (struct node *)malloc(sizeof(struct node)); // Yeni düğüm için bellekten yer ayır
    yeni->data = x;                                                 // Düğümün veri kısmına x değerini ata
    yeni->left = yeni->right = NULL;                                // Sol ve sağ çocukları başlangıçta NULL yap
    return yeni;                                                    // Oluşturulan düğümün adresini geri döndür
}

int main()
{
    struct node *tree = newNode(1);  // Kök düğümü oluştur (Değer: 1)
    tree->left = newNode(5);         // Kök düğümünün soluna yeni bir düğüm ekle (Değer: 5)
    tree->right = newNode(10);       // Kök düğümünün sağına yeni bir düğüm ekle (Değer: 10)
    tree->left->right = newNode(3);  // Sol çocuğun (5) sağına yeni bir düğüm ekle (Değer: 3)
    tree->right->right = newNode(6); // Sağ çocuğun (10) sağına yeni bir düğüm ekle (Değer: 6)

    // Oluşturulan ağacın yapısı:
    /*
            1
           / \
          5   10
           \     \
            3     6
    */

    return 0; // Programın başarılı şekilde sonlanması
}

//--------İKİLİ AĞACI İNORDER  İLE GEZME----------
void inorder(struct node *x)
{
    if (x == NULL) // Eğer düğüm NULL ise (boş ağaç veya yaprak düğümün çocuğu)
        return;
    inorder(x->left);        // 1️⃣ Önce sol alt ağacı ziyaret et
    printf("%d\t", x->data); // 2️⃣ Kökü yazdır
    inorder(x->right);       // 3️⃣ Sonra sağ alt ağacı ziyaret et
}

//-------İKİLİ AĞACI PREORDER İLE GEZME-------
void preorder(struct node *x)
{
    if (x == NULL) // Eğer düğüm NULL ise (boş ağaç veya yaprak düğümün çocuğu)
        return;
    printf("%d\t", x->data); // 1️⃣ Kökü yazdır
    preorder(x->left);       // 2️⃣ Sol alt ağacı ziyaret et
    preorder(x->right);      // 3️⃣ Sağ alt ağacı ziyaret et
}

//-----------İKİLİ AĞACI POSTORDER İLE GEZME--------------
void postorder(struct node *x)
{
    if (x == NULL) // Eğer düğüm NULL ise (boş ağaç veya yaprak düğümün çocuğu)
        return;
    postorder(x->left);      // 1️⃣ Sol alt ağacı ziyaret et
    postorder(x->right);     // 2️⃣ Sağ alt ağacı ziyaret et
    printf("%d\t", x->data); // 3️⃣ Kökü yazdır
}

//------------İKİLİ AĞACIN AYNASINI OLUŞTURMA--------------

struct node *mirror(struct node *root)
{
    if (root == NULL)
    {
        return NULL;
    } // Eğer ağaç boşsa (NULL), hiçbir işlem yapmadan geri dön.
    struct node *tmp = root->left; // Geçici bir değişkende sol çocuğu sakla.
    root->left = mirror(root->right); // Sağ alt ağacı aynaya çevir ve sol çocuğa ata.
    root->right = mirror(tmp); // Önceden kaydettiğimiz sol alt ağacı aynaya çevir ve sağ çocuğa ata.
    return root; // Yeni ayna ağacının kökünü döndür.
}

//----------------İKİLİ AĞACI BELLEKTEN SİLMEK-------------
void sil(struct node *root)
{
    if (root == NULL)
    {
        return;
    } // Eğer düğüm NULL ise, işlem yapmadan geri dön.
    sil(root->left);  // Önce sol alt ağacı sil.
    sil(root->right); // Sonra sağ alt ağacı sil.
    free(root); // En son kök düğümü bellekte serbest bırak.
}

//----------YENİ DÜĞÜM EKLEME-------
struct tree *insert(struct tree *root, int x)
{
    if (root == NULL)
    {
        return createNode(x);} // Eğer kök boşsa, yeni düğüm oluştur ve döndür.

    if (x < root->data)
    { // Eğer x değeri kökteki veriden küçükse, sol alt ağaca ekle.
        root->left = insert(root->left, x);}
    else
    { // Eğer x değeri kökteki veriden büyükse, sağ alt ağaca ekle.
        root->right = insert(root->right, x);
    }

    return root; // Güncellenmiş kök düğümü döndür.
}

//---------------DÜĞÜM ARAMA---------------
    struct tree *bul(struct tree *root, int x)
{
    if (root == NULL || root->data == x)
    {
     return root;} // Eğer ağaç boşsa veya değer bulunduysa düğümü döndür.

    if (x < root->data)
    {
        return bul(root->left, x);} // Eğer x, root->data'dan küçükse, sol alt ağaçta ara.

    return bul(root->right, x); // Eğer x, root->data'dan büyükse, sağ alt ağaçta ara.
}

//------------AĞACIN BİNARY TREE OLUP OLMADIĞINI KONTROL------

int kontrol(struct tree *root)
{
    if (root == NULL)
    {
        return 1; } // Eğer ağaç boşsa, geçerli bir BST'dir.
    if (root->left != NULL && root->left->data > root->data)
    {
        return 0;} // Sol çocuğun değeri büyükse BST değil.
    if (root->right != NULL && root->right->data < root->data)
    {
        return 0;} // Sağ çocuğun değeri küçükse BST değil.
    if (!kontrol(root->left) || !kontrol(root->right))
    {
        return 0; } // Sol veya sağ alt ağaç BST değilse geçersiz.
    return 1; // Tüm kontrollerden geçtiyse BST'dir.
}


//--------------AĞAÇTAKİ TÜM YAPRAKLARI SİLME------------
struct tree *leaveD(struct tree *root)
{
    if (root->left == NULL && root->right == NULL)
    {                // Eğer düğüm bir yaprak düğümse (alt düğümü yok)
        free(root);  // Bellekten kaldır
        return NULL; // NULL döndür (üst düğüme bağlantıyı kaldır)
    }

    root->left = leaveD(root->left);   // Sol alt ağacın yapraklarını sil
    root->right = leaveD(root->right); // Sağ alt ağacın yapraklarını sil

    return root; // Güncellenmiş kökü döndür
}
