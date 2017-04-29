#ifndef TYPE_COLLECTION
#define TYPE_COLLECTION

struct NullType {};

template <typename T, typename U>
struct TypeCollection {
	using Head = T;
	using Tail = U;
};

template <typename...>
struct TypeCollectionMake;

template <>
struct TypeCollectionMake<> {
	using Collection = NullType;
};

template <typename Head, typename... Types>
struct TypeCollectionMake<Head, Types...> {
	using Collection = TypeCollection<Head, typename TypeCollectionMake<Types...>::Collection>;
};

// Длина
template <typename> struct Length;

template <>
struct Length<NullType> {
	enum { value = 0 };
};

template <typename Head, typename Tail>
struct Length<TypeCollection<Head, Tail>> {
	enum { value = Length<Tail>::value + 1 };
};

//  Получение индекса эл-та
template <typename, typename> struct IndexOf;

template <typename T>
struct IndexOf<NullType, T> {
	enum { value = -1 };
};

template <typename T, typename Tail>
struct IndexOf<TypeCollection<T, Tail>, T> {
	enum { value = 0 };
};

template <typename Head, typename Tail, typename T>
struct IndexOf<TypeCollection<Head, Tail>, T> {
	using Collection = IndexOf<Tail, T>;
	enum { value = Collection::value == -1 ? -1 : Collection::value + 1 };
};



// Получить доступ к элементу
template <class TList, unsigned int index, typename DefaultType = NullType>
struct GetElement
{
	typedef DefaultType Collection;
};

template <class Head, class Tail, typename DefaultType>
struct GetElement<TypeCollection<Head, Tail>, 0, DefaultType>
{
	typedef Head Collection;
};

template <class Head, class Tail, unsigned int i, typename DefaultType>
struct GetElement<TypeCollection<Head, Tail>, i, DefaultType>
{
	typedef typename GetElement<Tail, i - 1, DefaultType>::Collection Collection;
};

#endif