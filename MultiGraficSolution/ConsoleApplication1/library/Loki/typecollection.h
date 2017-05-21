#ifndef TYPE_COLLECTION2
#define TYPE_COLLECTION2

namespace typeCollectionNew
{
	struct NullTypeCol {};

	template <typename T, typename U>
	struct TypeCollection {
		using Head = T;
		using Tail = U;
	};

	template <typename...>
	struct TypeCollectionMake;

	template <>
	struct TypeCollectionMake<> {
		using Collection = NullTypeCol;
	};

	template <typename Head, typename... Types>
	struct TypeCollectionMake<Head, Types...> {
		using Collection = TypeCollection<Head, typename TypeCollectionMake<Types...>::Collection>;
	};

	// �����
	template <typename> struct Length;

	template <>
	struct Length<NullTypeCol> {
		enum { value = 0 };
	};

	template <typename Head, typename Tail>
	struct Length<TypeCollection<Head, Tail>> {
		enum { value = Length<Tail>::value + 1 };
	};

	//  ��������� ������� ��-��
	template <typename, typename> struct IndexOf;

	template <typename T>
	struct IndexOf<NullTypeCol, T> {
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



	// �������� ������ � ��������
	template <class TList, unsigned int index, typename DefaultType = NullTypeCol>
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
}
#endif