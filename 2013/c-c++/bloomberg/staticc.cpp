class B {};
class D : public B {};

int main() {
 D d;
 B b;
 b = static_cast<B>(d);
 d = static_cast<D>(b);
}
