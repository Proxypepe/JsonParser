#include "DataType.h"


void IntType::accept(IVisitor* visitor) const
{
	visitor->visit(this);
}

void StringType::accept(IVisitor* visitor) const
{
	visitor->visit(this);
}

void ArrayIntType::accept(IVisitor* visitor) const
{
	visitor->visit(this);
}

void ArrayStringType::accept(IVisitor* visitor) const
{
	visitor->visit(this);
}

void BoolType::accept(IVisitor* visitor) const
{
	visitor->visit(this);
}

void ObjectType::accept(IVisitor* visitor) const
{
	visitor->visit(this);
}
