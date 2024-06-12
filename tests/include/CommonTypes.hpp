#pragma once

#include <memory>
#include <print>

struct A
{
};

struct B
{
};

struct C
{
    C(B) {}
};

struct D
{
    D(A, B, C) {}
};

struct E
{
    E(A, B) {}
};

struct Eshared
{
    Eshared(std::shared_ptr<A>, std::shared_ptr<B>) {}

    void hello()
    {
        std::println("Hello");
    }
};

struct I
{
    virtual ~I() = default;
    virtual int foo() = 0;
};

struct Ia : public I
{
    int foo() override
    {
        return 42;
    };
};

struct Ib : public I
{
    int foo() override
    {
        return 69;
    };
};

struct DependsOnI
{
    DependsOnI(std::shared_ptr<I>) {}
};

struct IEshared : public I
{
    IEshared(std::shared_ptr<A>) {}

    int foo() override
    {
        return 88;
    };
};

struct Mock : public I
{
    int foo() override
    {
        return -1;
    }
};

struct Aa
{
    int bar()
    {
        return 2;
    }
};

struct Bb
{
    Bb(std::shared_ptr<Aa> _aa) : aa(_aa) {}

    int baz()
    {
        return 2 * aa->bar(); // 4
    }

    std::shared_ptr<Aa> aa;
};

struct Cc
{
    Cc(std::shared_ptr<Bb> _bb) : bb(_bb) {}

    int foo()
    {
        return bb->baz() * 4; // 16
    }

    std::shared_ptr<Bb> bb;
};

struct Dd
{
    Dd(std::shared_ptr<Aa> _aa, std::shared_ptr<Cc> _cc) : aa(_aa), cc(_cc) {}

    int xyz()
    {
        return aa->bar() * cc->foo(); // 32
    }

    std::shared_ptr<Aa> aa;
    std::shared_ptr<Cc> cc;
};

struct Ee
{
    Ee(std::shared_ptr<Dd> _dd, std::shared_ptr<Bb> _bb) : dd(_dd), bb(_bb) {}

    int tuv()
    {
        return dd->xyz() * bb->baz(); // 128
    }

    std::shared_ptr<Dd> dd;
    std::shared_ptr<Bb> bb;
};
