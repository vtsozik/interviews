/*

The code provided defines a set of 'PipelineProducer' and 'PipelineConsumer' classes.
Read through the code to get an understanding of how it works. Your task is to
define a new 'PipelineConsumer' component which does the following:

On receiving an integer, it should:

If the input is even, immediately produce the input
If the input is odd, store it. If you have 3 stored odds, produce them all immediately
Only produce any odd number once

*/

#include <cstddef>
#include <iostream>
#include <list>

template <typename Input>
class PipeConsumer {

public:
    virtual void handle(Input input) = 0;
};

template <typename Output>
class PipeProducer {
    PipeConsumer<Output> *d_nextSegment;
protected:
    void produce(Output output);

public:
    explicit PipeProducer(PipeConsumer<Output> *nextSegment = nullptr);
    PipeConsumer<Output>* connect(PipeConsumer<Output> *nextSegment);
};

template <typename Output>
PipeProducer<Output>::PipeProducer( PipeConsumer<Output> *nextSegment ) :
    d_nextSegment(nextSegment)
{
}

template <typename Output>
void PipeProducer<Output>::produce(Output output)
{
    d_nextSegment->handle(output);
}

template <typename Output>
PipeConsumer<Output>* PipeProducer<Output>::connect(PipeConsumer<Output> *nextSegment)
{
    d_nextSegment = nextSegment;
    return d_nextSegment;
}

class IntProducer : public PipeProducer<int> {
public:
    void go();
};

void IntProducer::go()
{
    for(int i = 0; i < 100; ++i) {
        produce(i);
    }
}

// Here, we need a new pipeline component
// On receiving an integer, it should:
// 1) If the input is even, immediately produce the input
// 2) If the input is odd, store it.  If you have 3 stored odds, produce them all immediately
// 2a) Only produce any odd number once

class Cutter : public PipeConsumer<int>, public PipeProducer<double> {
private:
    double d_cutFactor;
public:
    explicit Cutter(double cutFactor);
    void handle(int input);
};

Cutter::Cutter(double cutFactor) :
    d_cutFactor(cutFactor)
{
}

void Cutter::handle(int input)
{
    produce( static_cast<double>(input) / d_cutFactor );
}


class Outputter : public PipeConsumer<double> {
    void handle(double input);
};

void Outputter::handle(double input)
{
    std::cout << input << std::endl;
}

class Processor : public PipeConsumer<double>, public PipeProducer<double>
{
    size_t m_s;
    std::list<int> m_l;

public:
    Processor(size_t s): m_s(3) { }

    void handle(double input)
    {
        int in = static_cast<int>(input);
        if ((in & 1) == 0)
        {
            produce(static_cast<double>(in));
        }
        else 
        {
            m_l.push_back(in);
            if (m_l.size() == m_s)
            {
                for (auto li : m_l)
                {
                    produce(static_cast<double>(li));
                }
		m_l.clear();
            }
        }
    }
};

int main()
{
    IntProducer producer;
    Cutter      cutter(2);
    Processor processor(3);
    Outputter   outputter;
    producer.connect(&cutter);
    cutter.connect(&processor);
    processor.connect(&outputter);

    producer.go();
}
