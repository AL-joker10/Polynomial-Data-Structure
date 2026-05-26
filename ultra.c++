#include <iostream>
using namespace std;

// 1. تعريف الهيكل البنائي للنود (الحد في المعادلة)
struct node 
{ 
    int coef;       // المعامل (الرقم المضروب في x)
    int power;      // الأُس (القوة المرفوع لها x)
    node* next;     // مؤشر بيشاور على الحد اللي بعده
}; 

// عمل اسم مستعار للمؤشر لتسهيل الكتابة
typedef node* poly;      

// دالة مساعدة لحجز نود جديدة في الذاكرة وتعبئة بياناتها
poly make_new_node(int coef, int power) {
    poly p = new node;
    p->coef = coef;
    p->power = power;
    p->next = NULL;
    return p;
}

// 2. الدالة المساعدة للإضافة في نهاية القائمة بكفاءة O(1)
void insert_at_end(poly &c, poly &t, int coef, int power) 
{ 
    poly p = make_new_node(coef, power); 
    
    if (c == NULL) // إذا كانت قائمة الناتج فارغة تماماً
    { 
        c = p;   // مؤشر البداية يمسك أول نود
        t = p;   // مؤشر النهاية يمسك نفس النود
    } 
    else // إذا كانت تحتوي على حدود مسبقاً
    { 
        t->next = p; // ربط النود الأخيرة القديمة بالنود الجديدة
        t = p;       // تحريك مؤشر النهاية (t) ليقف على الذيل الجديد
    } 
}

// 3. الدالة الرئيسية لجمع المعادلتين (خوارزمية الدمج)
void poly_add(poly a, poly b, poly &c) 
{ 
    poly p, q;      // مؤشرات للحركة عبر القوائم a و b
    poly t;         // مؤشر يشير إلى آخر نود في القائمة c
    int temp; 
    
    p = a; 
    q = b; 
    c = NULL; 
    t = NULL; 
    
    // حلقة الدمج الرئيسية (المقارنة الثنائية بالتوازي)
    while ((p != NULL) && (q != NULL))     
    {
        if (p->power < q->power) // حالة: أُس القائمة a أصغر
        {
            insert_at_end(c, t, p->coef, p->power); 
            p = p->next; 
        }
        else if (q->power < p->power) // حالة: أُس القائمة b أصغر
        {
            insert_at_end(c, t, q->coef, q->power); 
            q = q->next; 
        }
        else // حالة: تساوي الأسُس (الدمج الجبري)
        { 
            temp = p->coef + q->coef; 
            if (temp != 0)  // نضمن عدم تخزين الحدود الصفرية
            {
                insert_at_end(c, t, temp, p->power); 
            }
            p = p->next;   
            q = q->next; 
        }
    } 
    
    // مرحلة معالجة الحدود المتبقية من القائمة a
    while (p != NULL)  
    {
        insert_at_end(c, t, p->coef, p->power); 
        p = p->next; 
    }
    
    // مرحلة معالجة الحدود المتبقية من القائمة b
    while (q != NULL)  
    {
        insert_at_end(c, t, q->coef, q->power); 
        q = q->next; 
    }
}

// دالة مساعدة لطباعة المعادلة بشكل رياضي منظم
void print_poly(poly head) {
    if (head == NULL) {
        cout << "0";
        return;
    }
    poly curr = head;
    while (curr != NULL) {
        cout << curr->coef << "x^" << curr->power;
        curr = curr->next;
        if (curr != NULL) cout << " + ";
    }
    cout << endl;
}

// 4. دالة التشغيل الرئيسية لتجربة الخوارزمية لايف
int main() {
    poly a = NULL, tA = NULL;
    poly b = NULL, tB = NULL;
    poly c = NULL; // قائمة الناتج
    
    // بناء المعادلة الأولى A: 3x^1 + 5x^3 (مرتبة تصاعدياً)
    insert_at_end(a, tA, 3, 1);
    insert_at_end(a, tA, 5, 3);
    
    // بناء المعادلة الثانية B: 2x^1 + 4x^2 + 6x^4
    insert_at_end(b, tB, 2, 1);
    insert_at_end(b, tB, 4, 2);
    insert_at_end(b, tB, 6, 4);
    
    // طباعة المدخلات
    cout << "Polynomial A: ";
    print_poly(a);
    
    cout << "Polynomial B: ";
    print_poly(b);
    
    // استدعاء خوارزمية الجمع المطور
    poly_add(a, b, c);
    
    // طباعة النتيجة النهائية
    cout << "Sum (Polynomial C): ";
    print_poly(c); 
    // الناتج المتوقع والمظبوط: 5x^1 + 4x^2 + 5x^3 + 6x^4
    
    return 0;
}