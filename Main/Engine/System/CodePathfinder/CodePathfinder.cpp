#include "CodePathfinder.h"

LDDrift::CodePathfinder::CodePathfinder() = default;

LDDrift::CodePathfinder::~CodePathfinder() = default;

void LDDrift::CodePathfinder::initializeCodePathfinder() {
    KeyWords.reserve(1200);
    // ==================== Conditions ====================
    KeyWords.emplace_back("if");
    KeyWords.emplace_back("else");
    KeyWords.emplace_back("switch");
    KeyWords.emplace_back("case");
    KeyWords.emplace_back("default");

    // ==================== Loops ====================
    KeyWords.emplace_back("for");
    KeyWords.emplace_back("while");
    KeyWords.emplace_back("do");
    KeyWords.emplace_back("break");
    KeyWords.emplace_back("continue");

    // ==================== Jump statements ====================
    KeyWords.emplace_back("return");
    KeyWords.emplace_back("goto");

    // ==================== Fundamental types ====================
    KeyWords.emplace_back("bool");
    KeyWords.emplace_back("char");
    KeyWords.emplace_back("char8_t");
    KeyWords.emplace_back("char16_t");
    KeyWords.emplace_back("char32_t");
    KeyWords.emplace_back("wchar_t");
    KeyWords.emplace_back("short");
    KeyWords.emplace_back("int");
    KeyWords.emplace_back("long");
    KeyWords.emplace_back("float");
    KeyWords.emplace_back("double");
    KeyWords.emplace_back("signed");
    KeyWords.emplace_back("unsigned");
    KeyWords.emplace_back("void");

    // ==================== Type declarations ====================
    KeyWords.emplace_back("auto");
    KeyWords.emplace_back("class");
    KeyWords.emplace_back("struct");
    KeyWords.emplace_back("union");
    KeyWords.emplace_back("enum");
    KeyWords.emplace_back("typename");
    KeyWords.emplace_back("decltype");
    KeyWords.emplace_back("typedef");
    KeyWords.emplace_back("using");
    KeyWords.emplace_back("concept");
    KeyWords.emplace_back("requires");

    // ==================== Type qualifiers ====================
    KeyWords.emplace_back("const");
    KeyWords.emplace_back("volatile");
    KeyWords.emplace_back("mutable");
    KeyWords.emplace_back("constexpr");
    KeyWords.emplace_back("consteval");
    KeyWords.emplace_back("constinit");
    KeyWords.emplace_back("static");
    KeyWords.emplace_back("thread_local");
    KeyWords.emplace_back("inline");
    KeyWords.emplace_back("extern");
    KeyWords.emplace_back("register");

    // ==================== Access specifiers ====================
    KeyWords.emplace_back("public");
    KeyWords.emplace_back("private");
    KeyWords.emplace_back("protected");
    KeyWords.emplace_back("friend");
    KeyWords.emplace_back("virtual");
    KeyWords.emplace_back("explicit");
    KeyWords.emplace_back("override");
    KeyWords.emplace_back("final");

    // ==================== Namespaces and templates ====================
    KeyWords.emplace_back("namespace");
    KeyWords.emplace_back("template");
    KeyWords.emplace_back("export");
    KeyWords.emplace_back("module");
    KeyWords.emplace_back("import");

    // ==================== Memory management ====================
    KeyWords.emplace_back("new");
    KeyWords.emplace_back("delete");

    // ==================== Type conversions ====================
    KeyWords.emplace_back("static_cast");
    KeyWords.emplace_back("dynamic_cast");
    KeyWords.emplace_back("const_cast");
    KeyWords.emplace_back("reinterpret_cast");

    // ==================== Operators and expressions ====================
    KeyWords.emplace_back("operator");
    KeyWords.emplace_back("sizeof");
    KeyWords.emplace_back("alignas");
    KeyWords.emplace_back("alignof");
    KeyWords.emplace_back("noexcept");
    KeyWords.emplace_back("typeid");
    KeyWords.emplace_back("asm");

    // ==================== Exception handling ====================
    KeyWords.emplace_back("try");
    KeyWords.emplace_back("catch");
    KeyWords.emplace_back("throw");

    // ==================== Boolean and null literals ====================
    KeyWords.emplace_back("true");
    KeyWords.emplace_back("false");
    KeyWords.emplace_back("nullptr");

    // ==================== Other language constructs ====================
    KeyWords.emplace_back("this");
    KeyWords.emplace_back("static_assert");
    KeyWords.emplace_back("contract_assert");

    // ==================== Alternative operator keywords ====================
    KeyWords.emplace_back("and");
    KeyWords.emplace_back("and_eq");
    KeyWords.emplace_back("bitand");
    KeyWords.emplace_back("bitor");
    KeyWords.emplace_back("compl");
    KeyWords.emplace_back("not");
    KeyWords.emplace_back("not_eq");
    KeyWords.emplace_back("or");
    KeyWords.emplace_back("or_eq");
    KeyWords.emplace_back("xor");
    KeyWords.emplace_back("xor_eq");

    // ==================== Coroutines ====================
    KeyWords.emplace_back("co_await");
    KeyWords.emplace_back("co_return");
    KeyWords.emplace_back("co_yield");

    // ==================== Contextual keywords / special identifiers ====================
    KeyWords.emplace_back("override");
    KeyWords.emplace_back("final");
    KeyWords.emplace_back("import");
    KeyWords.emplace_back("module");
    KeyWords.emplace_back("pre");
    KeyWords.emplace_back("post");
    // ==================== Preprocessor ====================
    KeyWords.emplace_back("#include");
    KeyWords.emplace_back("#include_next");
    KeyWords.emplace_back("#define");
    KeyWords.emplace_back("#undef");

    KeyWords.emplace_back("#if");
    KeyWords.emplace_back("#ifdef");
    KeyWords.emplace_back("#ifndef");
    KeyWords.emplace_back("#elif");
    KeyWords.emplace_back("#else");
    KeyWords.emplace_back("#endif");

    KeyWords.emplace_back("#pragma");
    KeyWords.emplace_back("#error");
    KeyWords.emplace_back("#warning");
    KeyWords.emplace_back("#line");

    // ==================== Common preprocessor macros ====================
    KeyWords.emplace_back("__FILE__");
    KeyWords.emplace_back("__LINE__");
    KeyWords.emplace_back("__DATE__");
    KeyWords.emplace_back("__TIME__");
    KeyWords.emplace_back("__cplusplus");
    KeyWords.emplace_back("__func__");
    KeyWords.emplace_back("__VA_ARGS__");
    KeyWords.emplace_back("__VA_OPT__");
    KeyWords.emplace_back("_Pragma");

    // ==================== Include guards ====================
    KeyWords.emplace_back("HEADER_H");
    KeyWords.emplace_back("HEADER_HPP");
    KeyWords.emplace_back("PRAGMA_ONCE");
    // ==================== Sequence containers ====================
    KeyWords.emplace_back("std::array");
    KeyWords.emplace_back("std::vector");
    KeyWords.emplace_back("std::deque");
    KeyWords.emplace_back("std::list");
    KeyWords.emplace_back("std::forward_list");
    KeyWords.emplace_back("std::inplace_vector"); // C++26

    // ==================== Associative containers ====================
    KeyWords.emplace_back("std::set");
    KeyWords.emplace_back("std::multiset");
    KeyWords.emplace_back("std::map");
    KeyWords.emplace_back("std::multimap");

    // ==================== Unordered containers ====================
    KeyWords.emplace_back("std::unordered_set");
    KeyWords.emplace_back("std::unordered_multiset");
    KeyWords.emplace_back("std::unordered_map");
    KeyWords.emplace_back("std::unordered_multimap");

    // ==================== Container adaptors ====================
    KeyWords.emplace_back("std::stack");
    KeyWords.emplace_back("std::queue");
    KeyWords.emplace_back("std::priority_queue");

    // ==================== C++23 / C++26 containers ====================
    KeyWords.emplace_back("std::flat_map"); // C++23
    KeyWords.emplace_back("std::flat_multimap"); // C++23
    KeyWords.emplace_back("std::flat_set"); // C++23
    KeyWords.emplace_back("std::flat_multiset"); // C++23
    KeyWords.emplace_back("std::hive"); // C++26

    // ==================== Views and non-owning sequences ====================
    KeyWords.emplace_back("std::span");
    KeyWords.emplace_back("std::mdspan");
    KeyWords.emplace_back("std::string_view");
    KeyWords.emplace_back("std::wstring_view");
    KeyWords.emplace_back("std::u8string_view");
    KeyWords.emplace_back("std::u16string_view");
    KeyWords.emplace_back("std::u32string_view");

    // ==================== Strings ====================
    KeyWords.emplace_back("std::string");
    KeyWords.emplace_back("std::wstring");
    KeyWords.emplace_back("std::u8string");
    KeyWords.emplace_back("std::u16string");
    KeyWords.emplace_back("std::u32string");
    KeyWords.emplace_back("std::basic_string");

    // ==================== Pairs, tuples and aggregates ====================
    KeyWords.emplace_back("std::pair");
    KeyWords.emplace_back("std::tuple");
    KeyWords.emplace_back("std::array");
    KeyWords.emplace_back("std::initializer_list");
    KeyWords.emplace_back("std::optional");
    KeyWords.emplace_back("std::variant");
    KeyWords.emplace_back("std::any");
    KeyWords.emplace_back("std::expected");
    KeyWords.emplace_back("std::bitset");
    KeyWords.emplace_back("std::valarray");

    // ==================== Complex numbers ====================
    KeyWords.emplace_back("std::complex");
    KeyWords.emplace_back("std::numbers");
    // ==================== Smart pointers ====================
    KeyWords.emplace_back("std::unique_ptr");
    KeyWords.emplace_back("std::shared_ptr");
    KeyWords.emplace_back("std::weak_ptr");
    KeyWords.emplace_back("std::auto_ptr"); // منسوخ و حذف‌شده در استانداردهای جدید

    // ==================== Smart pointer creation ====================
    KeyWords.emplace_back("std::make_unique");
    KeyWords.emplace_back("std::make_shared");
    KeyWords.emplace_back("std::allocate_shared");
    KeyWords.emplace_back("std::make_unique_for_overwrite");
    KeyWords.emplace_back("std::make_shared_for_overwrite");

    // ==================== Memory utilities ====================
    KeyWords.emplace_back("std::allocator");
    KeyWords.emplace_back("std::allocator_traits");
    KeyWords.emplace_back("std::addressof");
    KeyWords.emplace_back("std::construct_at");
    KeyWords.emplace_back("std::destroy_at");
    KeyWords.emplace_back("std::destroy");
    KeyWords.emplace_back("std::destroy_n");
    KeyWords.emplace_back("std::align");
    KeyWords.emplace_back("std::assume_aligned");

    // ==================== Pointer helpers ====================
    KeyWords.emplace_back("std::to_address");
    KeyWords.emplace_back("std::pointer_traits");
    KeyWords.emplace_back("std::owner_less");
    KeyWords.emplace_back("std::get_deleter");

    // ==================== Resource management ====================
    KeyWords.emplace_back("std::unique_lock");
    KeyWords.emplace_back("std::shared_lock");
    KeyWords.emplace_back("std::lock_guard");
    KeyWords.emplace_back("std::scoped_lock");
    KeyWords.emplace_back("std::jthread");
    KeyWords.emplace_back("std::lock");
    KeyWords.emplace_back("std::try_lock");
    KeyWords.emplace_back("std::unlock");
    // ==================== Move and forwarding ====================
    KeyWords.emplace_back("std::move");
    KeyWords.emplace_back("std::forward");
    KeyWords.emplace_back("std::move_if_noexcept");
    KeyWords.emplace_back("std::forward_like");
    KeyWords.emplace_back("std::exchange");
    KeyWords.emplace_back("std::swap");
    KeyWords.emplace_back("std::swap_ranges");

    // ==================== Pair and tuple utilities ====================
    KeyWords.emplace_back("std::make_pair");
    KeyWords.emplace_back("std::make_tuple");
    KeyWords.emplace_back("std::tie");
    KeyWords.emplace_back("std::forward_as_tuple");
    KeyWords.emplace_back("std::apply");
    KeyWords.emplace_back("std::make_from_tuple");
    KeyWords.emplace_back("std::get");
    KeyWords.emplace_back("std::tuple_size");
    KeyWords.emplace_back("std::tuple_element");

    // ==================== Common utility functions ====================
    KeyWords.emplace_back("std::min");
    KeyWords.emplace_back("std::max");
    KeyWords.emplace_back("std::minmax");
    KeyWords.emplace_back("std::clamp");
    KeyWords.emplace_back("std::min_element");
    KeyWords.emplace_back("std::max_element");
    KeyWords.emplace_back("std::exchange");
    KeyWords.emplace_back("std::as_const");
    KeyWords.emplace_back("std::to_underlying");
    KeyWords.emplace_back("std::cmp_equal");
    KeyWords.emplace_back("std::cmp_not_equal");
    KeyWords.emplace_back("std::cmp_less");
    KeyWords.emplace_back("std::cmp_greater");
    KeyWords.emplace_back("std::cmp_less_equal");
    KeyWords.emplace_back("std::cmp_greater_equal");

    // ==================== Function objects and invocation ====================
    KeyWords.emplace_back("std::function");
    KeyWords.emplace_back("std::invoke");
    KeyWords.emplace_back("std::invoke_result");
    KeyWords.emplace_back("std::bind");
    KeyWords.emplace_back("std::bind_front");
    KeyWords.emplace_back("std::bind_back");
    KeyWords.emplace_back("std::ref");
    KeyWords.emplace_back("std::cref");
    KeyWords.emplace_back("std::reference_wrapper");
    KeyWords.emplace_back("std::mem_fn");
    KeyWords.emplace_back("std::not_fn");
    KeyWords.emplace_back("std::identity");

    // ==================== Common functional objects ====================
    KeyWords.emplace_back("std::plus");
    KeyWords.emplace_back("std::minus");
    KeyWords.emplace_back("std::multiplies");
    KeyWords.emplace_back("std::divides");
    KeyWords.emplace_back("std::modulus");
    KeyWords.emplace_back("std::negate");
    KeyWords.emplace_back("std::equal_to");
    KeyWords.emplace_back("std::not_equal_to");
    KeyWords.emplace_back("std::greater");
    KeyWords.emplace_back("std::greater_equal");
    KeyWords.emplace_back("std::less");
    KeyWords.emplace_back("std::less_equal");
    KeyWords.emplace_back("std::logical_and");
    KeyWords.emplace_back("std::logical_or");
    KeyWords.emplace_back("std::logical_not");
    KeyWords.emplace_back("std::bit_and");
    KeyWords.emplace_back("std::bit_or");
    KeyWords.emplace_back("std::bit_xor");
    KeyWords.emplace_back("std::bit_not");
    // ==================== Sorting ====================
    KeyWords.emplace_back("std::sort");
    KeyWords.emplace_back("std::stable_sort");
    KeyWords.emplace_back("std::partial_sort");
    KeyWords.emplace_back("std::nth_element");
    KeyWords.emplace_back("std::is_sorted");
    KeyWords.emplace_back("std::is_sorted_until");
    KeyWords.emplace_back("std::partial_sort_copy");

    // ==================== Searching ====================
    KeyWords.emplace_back("std::find");
    KeyWords.emplace_back("std::find_if");
    KeyWords.emplace_back("std::find_if_not");
    KeyWords.emplace_back("std::find_end");
    KeyWords.emplace_back("std::find_first_of");
    KeyWords.emplace_back("std::search");
    KeyWords.emplace_back("std::search_n");
    KeyWords.emplace_back("std::binary_search");
    KeyWords.emplace_back("std::lower_bound");
    KeyWords.emplace_back("std::upper_bound");
    KeyWords.emplace_back("std::equal_range");

    // ==================== Counting and comparison ====================
    KeyWords.emplace_back("std::count");
    KeyWords.emplace_back("std::count_if");
    KeyWords.emplace_back("std::all_of");
    KeyWords.emplace_back("std::any_of");
    KeyWords.emplace_back("std::none_of");
    KeyWords.emplace_back("std::equal");
    KeyWords.emplace_back("std::mismatch");
    KeyWords.emplace_back("std::lexicographical_compare");
    KeyWords.emplace_back("std::lexicographical_compare_three_way");

    // ==================== Transforming ====================
    KeyWords.emplace_back("std::copy");
    KeyWords.emplace_back("std::copy_if");
    KeyWords.emplace_back("std::copy_n");
    KeyWords.emplace_back("std::copy_backward");
    KeyWords.emplace_back("std::move");
    KeyWords.emplace_back("std::move_backward");
    KeyWords.emplace_back("std::transform");
    KeyWords.emplace_back("std::replace");
    KeyWords.emplace_back("std::replace_if");
    KeyWords.emplace_back("std::replace_copy");
    KeyWords.emplace_back("std::replace_copy_if");
    KeyWords.emplace_back("std::fill");
    KeyWords.emplace_back("std::fill_n");
    KeyWords.emplace_back("std::generate");
    KeyWords.emplace_back("std::generate_n");
    KeyWords.emplace_back("std::remove");
    KeyWords.emplace_back("std::remove_if");
    KeyWords.emplace_back("std::remove_copy");
    KeyWords.emplace_back("std::remove_copy_if");
    KeyWords.emplace_back("std::unique");
    KeyWords.emplace_back("std::unique_copy");
    KeyWords.emplace_back("std::reverse");
    KeyWords.emplace_back("std::reverse_copy");
    KeyWords.emplace_back("std::rotate");
    KeyWords.emplace_back("std::rotate_copy");
    KeyWords.emplace_back("std::shuffle");

    // ==================== Numeric algorithms ====================
    KeyWords.emplace_back("std::accumulate");
    KeyWords.emplace_back("std::reduce");
    KeyWords.emplace_back("std::transform_reduce");
    KeyWords.emplace_back("std::inner_product");
    KeyWords.emplace_back("std::partial_sum");
    KeyWords.emplace_back("std::inclusive_scan");
    KeyWords.emplace_back("std::exclusive_scan");
    KeyWords.emplace_back("std::adjacent_difference");
    KeyWords.emplace_back("std::iota");
    KeyWords.emplace_back("std::gcd");
    KeyWords.emplace_back("std::lcm");

    // ==================== Set algorithms ====================
    KeyWords.emplace_back("std::includes");
    KeyWords.emplace_back("std::set_union");
    KeyWords.emplace_back("std::set_intersection");
    KeyWords.emplace_back("std::set_difference");
    KeyWords.emplace_back("std::set_symmetric_difference");

    // ==================== Heap operations ====================
    KeyWords.emplace_back("std::make_heap");
    KeyWords.emplace_back("std::push_heap");
    KeyWords.emplace_back("std::pop_heap");
    KeyWords.emplace_back("std::sort_heap");
    KeyWords.emplace_back("std::is_heap");
    KeyWords.emplace_back("std::is_heap_until");

    // ==================== Permutations ====================
    KeyWords.emplace_back("std::next_permutation");
    KeyWords.emplace_back("std::prev_permutation");

    // ==================== Other algorithms ====================
    KeyWords.emplace_back("std::for_each");
    KeyWords.emplace_back("std::for_each_n");
    KeyWords.emplace_back("std::iter_swap");
    KeyWords.emplace_back("std::swap_ranges");
    KeyWords.emplace_back("std::partition");
    KeyWords.emplace_back("std::stable_partition");
    KeyWords.emplace_back("std::partition_copy");
    KeyWords.emplace_back("std::is_partitioned");
    KeyWords.emplace_back("std::max_element");
    KeyWords.emplace_back("std::min_element");
    KeyWords.emplace_back("std::clamp");
    KeyWords.emplace_back("std::sample");
    KeyWords.emplace_back("std::invoke");
    // ==================== Ranges ====================
    KeyWords.emplace_back("std::ranges");
    KeyWords.emplace_back("std::ranges::begin");
    KeyWords.emplace_back("std::ranges::end");
    KeyWords.emplace_back("std::ranges::size");
    KeyWords.emplace_back("std::ranges::empty");
    KeyWords.emplace_back("std::ranges::data");
    KeyWords.emplace_back("std::ranges::distance");
    KeyWords.emplace_back("std::ranges::advance");
    KeyWords.emplace_back("std::ranges::next");
    KeyWords.emplace_back("std::ranges::prev");

    // ==================== Ranges algorithms ====================
    KeyWords.emplace_back("std::ranges::sort");
    KeyWords.emplace_back("std::ranges::find");
    KeyWords.emplace_back("std::ranges::find_if");
    KeyWords.emplace_back("std::ranges::count");
    KeyWords.emplace_back("std::ranges::count_if");
    KeyWords.emplace_back("std::ranges::copy");
    KeyWords.emplace_back("std::ranges::transform");
    KeyWords.emplace_back("std::ranges::for_each");
    KeyWords.emplace_back("std::ranges::remove");
    KeyWords.emplace_back("std::ranges::remove_if");
    KeyWords.emplace_back("std::ranges::reverse");
    KeyWords.emplace_back("std::ranges::unique");
    KeyWords.emplace_back("std::ranges::partition");
    KeyWords.emplace_back("std::ranges::lower_bound");
    KeyWords.emplace_back("std::ranges::upper_bound");
    KeyWords.emplace_back("std::ranges::binary_search");
    KeyWords.emplace_back("std::ranges::all_of");
    KeyWords.emplace_back("std::ranges::any_of");
    KeyWords.emplace_back("std::ranges::none_of");

    // ==================== Range views ====================
    KeyWords.emplace_back("std::views");
    KeyWords.emplace_back("std::views::all");
    KeyWords.emplace_back("std::views::filter");
    KeyWords.emplace_back("std::views::transform");
    KeyWords.emplace_back("std::views::take");
    KeyWords.emplace_back("std::views::take_while");
    KeyWords.emplace_back("std::views::drop");
    KeyWords.emplace_back("std::views::drop_while");
    KeyWords.emplace_back("std::views::iota");
    KeyWords.emplace_back("std::views::join");
    KeyWords.emplace_back("std::views::split");
    KeyWords.emplace_back("std::views::reverse");
    KeyWords.emplace_back("std::views::keys");
    KeyWords.emplace_back("std::views::values");
    KeyWords.emplace_back("std::views::enumerate");
    KeyWords.emplace_back("std::views::zip");
    KeyWords.emplace_back("std::views::zip_transform");
    KeyWords.emplace_back("std::views::adjacent");
    KeyWords.emplace_back("std::views::chunk");
    KeyWords.emplace_back("std::views::stride");
    KeyWords.emplace_back("std::views::repeat");
    KeyWords.emplace_back("std::views::cartesian_product");
    // ==================== String operations ====================
    KeyWords.emplace_back("std::to_string");
    KeyWords.emplace_back("std::to_wstring");
    KeyWords.emplace_back("std::stoi");
    KeyWords.emplace_back("std::stol");
    KeyWords.emplace_back("std::stoll");
    KeyWords.emplace_back("std::stoul");
    KeyWords.emplace_back("std::stoull");
    KeyWords.emplace_back("std::stof");
    KeyWords.emplace_back("std::stod");
    KeyWords.emplace_back("std::stold");

    // ==================== Character handling ====================
    KeyWords.emplace_back("std::isalnum");
    KeyWords.emplace_back("std::isalpha");
    KeyWords.emplace_back("std::isdigit");
    KeyWords.emplace_back("std::islower");
    KeyWords.emplace_back("std::isupper");
    KeyWords.emplace_back("std::isspace");
    KeyWords.emplace_back("std::isprint");
    KeyWords.emplace_back("std::ispunct");
    KeyWords.emplace_back("std::isxdigit");
    KeyWords.emplace_back("std::tolower");
    KeyWords.emplace_back("std::toupper");

    // ==================== C-style string handling ====================
    KeyWords.emplace_back("std::strlen");
    KeyWords.emplace_back("std::strcmp");
    KeyWords.emplace_back("std::strncmp");
    KeyWords.emplace_back("std::strcpy");
    KeyWords.emplace_back("std::strncpy");
    KeyWords.emplace_back("std::strcat");
    KeyWords.emplace_back("std::strncat");
    KeyWords.emplace_back("std::strstr");
    KeyWords.emplace_back("std::strchr");
    KeyWords.emplace_back("std::strrchr");
    KeyWords.emplace_back("std::strtok");
    KeyWords.emplace_back("std::memcpy");
    KeyWords.emplace_back("std::memmove");
    KeyWords.emplace_back("std::memset");
    KeyWords.emplace_back("std::memcmp");
    KeyWords.emplace_back("std::memchr");

    // ==================== String formatting ====================
    KeyWords.emplace_back("std::format");
    KeyWords.emplace_back("std::format_to");
    KeyWords.emplace_back("std::format_to_n");
    KeyWords.emplace_back("std::formatted_size");
    KeyWords.emplace_back("std::vformat");
    KeyWords.emplace_back("std::print");
    KeyWords.emplace_back("std::println");

    // ==================== String views and spans ====================
    KeyWords.emplace_back("std::string_view");
    KeyWords.emplace_back("std::span");
    KeyWords.emplace_back("std::subrange");

    // ==================== Regular expressions ====================
    KeyWords.emplace_back("std::regex");
    KeyWords.emplace_back("std::regex_match");
    KeyWords.emplace_back("std::regex_search");
    KeyWords.emplace_back("std::regex_replace");
    KeyWords.emplace_back("std::regex_iterator");
    KeyWords.emplace_back("std::smatch");
    KeyWords.emplace_back("std::cmatch");
    KeyWords.emplace_back("std::match_results");
    KeyWords.emplace_back("std::regex_error");
    // ==================== Standard streams ====================
    KeyWords.emplace_back("std::cin");
    KeyWords.emplace_back("std::cout");
    KeyWords.emplace_back("std::cerr");
    KeyWords.emplace_back("std::clog");
    KeyWords.emplace_back("std::wcin");
    KeyWords.emplace_back("std::wcout");
    KeyWords.emplace_back("std::wcerr");
    KeyWords.emplace_back("std::wclog");

    // ==================== Stream classes ====================
    KeyWords.emplace_back("std::istream");
    KeyWords.emplace_back("std::ostream");
    KeyWords.emplace_back("std::iostream");
    KeyWords.emplace_back("std::ifstream");
    KeyWords.emplace_back("std::ofstream");
    KeyWords.emplace_back("std::fstream");
    KeyWords.emplace_back("std::istringstream");
    KeyWords.emplace_back("std::ostringstream");
    KeyWords.emplace_back("std::stringstream");
    KeyWords.emplace_back("std::streambuf");
    KeyWords.emplace_back("std::filebuf");

    // ==================== Stream manipulators ====================
    KeyWords.emplace_back("std::endl");
    KeyWords.emplace_back("std::flush");
    KeyWords.emplace_back("std::ends");
    KeyWords.emplace_back("std::setw");
    KeyWords.emplace_back("std::setfill");
    KeyWords.emplace_back("std::setprecision");
    KeyWords.emplace_back("std::setbase");
    KeyWords.emplace_back("std::showbase");
    KeyWords.emplace_back("std::noshowbase");
    KeyWords.emplace_back("std::fixed");
    KeyWords.emplace_back("std::scientific");
    KeyWords.emplace_back("std::hex");
    KeyWords.emplace_back("std::dec");
    KeyWords.emplace_back("std::oct");
    KeyWords.emplace_back("std::boolalpha");
    KeyWords.emplace_back("std::noboolalpha");
    KeyWords.emplace_back("std::left");
    KeyWords.emplace_back("std::right");
    KeyWords.emplace_back("std::internal");
    KeyWords.emplace_back("std::quoted");

    // ==================== Input/output operations ====================
    KeyWords.emplace_back("std::getline");
    KeyWords.emplace_back("std::put");
    KeyWords.emplace_back("std::get");
    KeyWords.emplace_back("std::ws");
    KeyWords.emplace_back("std::read");
    KeyWords.emplace_back("std::write");
    KeyWords.emplace_back("std::readsome");
    KeyWords.emplace_back("std::gcount");
    KeyWords.emplace_back("std::seekg");
    KeyWords.emplace_back("std::seekp");
    KeyWords.emplace_back("std::tellg");
    KeyWords.emplace_back("std::tellp");
    KeyWords.emplace_back("std::ios");
    KeyWords.emplace_back("std::ios_base");
    // ==================== Basic mathematics ====================
    KeyWords.emplace_back("std::abs");
    KeyWords.emplace_back("std::fabs");
    KeyWords.emplace_back("std::fmod");
    KeyWords.emplace_back("std::remainder");
    KeyWords.emplace_back("std::fma");
    KeyWords.emplace_back("std::max");
    KeyWords.emplace_back("std::min");
    KeyWords.emplace_back("std::minmax");
    KeyWords.emplace_back("std::clamp");

    // ==================== Powers and roots ====================
    KeyWords.emplace_back("std::pow");
    KeyWords.emplace_back("std::sqrt");
    KeyWords.emplace_back("std::cbrt");
    KeyWords.emplace_back("std::hypot");

    // ==================== Exponential and logarithmic functions ====================
    KeyWords.emplace_back("std::exp");
    KeyWords.emplace_back("std::exp2");
    KeyWords.emplace_back("std::expm1");
    KeyWords.emplace_back("std::log");
    KeyWords.emplace_back("std::log10");
    KeyWords.emplace_back("std::log2");
    KeyWords.emplace_back("std::log1p");

    // ==================== Trigonometry ====================
    KeyWords.emplace_back("std::sin");
    KeyWords.emplace_back("std::cos");
    KeyWords.emplace_back("std::tan");
    KeyWords.emplace_back("std::asin");
    KeyWords.emplace_back("std::acos");
    KeyWords.emplace_back("std::atan");
    KeyWords.emplace_back("std::atan2");
    KeyWords.emplace_back("std::sinh");
    KeyWords.emplace_back("std::cosh");
    KeyWords.emplace_back("std::tanh");

    // ==================== Rounding ====================
    KeyWords.emplace_back("std::ceil");
    KeyWords.emplace_back("std::floor");
    KeyWords.emplace_back("std::trunc");
    KeyWords.emplace_back("std::round");
    KeyWords.emplace_back("std::lround");
    KeyWords.emplace_back("std::llround");
    KeyWords.emplace_back("std::nearbyint");
    KeyWords.emplace_back("std::rint");

    // ==================== Floating-point helpers ====================
    KeyWords.emplace_back("std::isfinite");
    KeyWords.emplace_back("std::isinf");
    KeyWords.emplace_back("std::isnan");
    KeyWords.emplace_back("std::signbit");
    KeyWords.emplace_back("std::isnormal");
    KeyWords.emplace_back("std::fpclassify");
    KeyWords.emplace_back("std::nextafter");
    KeyWords.emplace_back("std::copysign");

    // ==================== Numeric limits and constants ====================
    KeyWords.emplace_back("std::numeric_limits");
    KeyWords.emplace_back("std::int8_t");
    KeyWords.emplace_back("std::int16_t");
    KeyWords.emplace_back("std::int32_t");
    KeyWords.emplace_back("std::int64_t");
    KeyWords.emplace_back("std::uint8_t");
    KeyWords.emplace_back("std::uint16_t");
    KeyWords.emplace_back("std::uint32_t");
    KeyWords.emplace_back("std::uint64_t");
    KeyWords.emplace_back("std::size_t");
    KeyWords.emplace_back("std::ptrdiff_t");
    KeyWords.emplace_back("std::intptr_t");
    KeyWords.emplace_back("std::uintptr_t");
    KeyWords.emplace_back("std::byte");
    KeyWords.emplace_back("std::bit_cast");
    KeyWords.emplace_back("std::has_single_bit");
    KeyWords.emplace_back("std::bit_width");
    KeyWords.emplace_back("std::bit_floor");
    KeyWords.emplace_back("std::bit_ceil");
    KeyWords.emplace_back("std::popcount");
    KeyWords.emplace_back("std::countl_zero");
    KeyWords.emplace_back("std::countr_zero");
    KeyWords.emplace_back("std::rotl");
    KeyWords.emplace_back("std::rotr");
    // ==================== Chrono ====================
    KeyWords.emplace_back("std::chrono");
    KeyWords.emplace_back("std::chrono::duration");
    KeyWords.emplace_back("std::chrono::time_point");
    KeyWords.emplace_back("std::chrono::system_clock");
    KeyWords.emplace_back("std::chrono::steady_clock");
    KeyWords.emplace_back("std::chrono::high_resolution_clock");
    KeyWords.emplace_back("std::chrono::duration_cast");
    KeyWords.emplace_back("std::chrono::time_point_cast");
    KeyWords.emplace_back("std::chrono::year");
    KeyWords.emplace_back("std::chrono::month");
    KeyWords.emplace_back("std::chrono::day");
    KeyWords.emplace_back("std::chrono::year_month_day");
    KeyWords.emplace_back("std::chrono::hh_mm_ss");

    // ==================== Duration literals ====================
    KeyWords.emplace_back("std::chrono::nanoseconds");
    KeyWords.emplace_back("std::chrono::microseconds");
    KeyWords.emplace_back("std::chrono::milliseconds");
    KeyWords.emplace_back("std::chrono::seconds");
    KeyWords.emplace_back("std::chrono::minutes");
    KeyWords.emplace_back("std::chrono::hours");

    // ==================== Random numbers ====================
    KeyWords.emplace_back("std::random_device");
    KeyWords.emplace_back("std::mt19937");
    KeyWords.emplace_back("std::mt19937_64");
    KeyWords.emplace_back("std::default_random_engine");
    KeyWords.emplace_back("std::uniform_int_distribution");
    KeyWords.emplace_back("std::uniform_real_distribution");
    KeyWords.emplace_back("std::normal_distribution");
    KeyWords.emplace_back("std::bernoulli_distribution");
    KeyWords.emplace_back("std::poisson_distribution");
    KeyWords.emplace_back("std::binomial_distribution");
    KeyWords.emplace_back("std::generate_canonical");
    KeyWords.emplace_back("std::seed_seq");
    // ==================== Filesystem ====================
    KeyWords.emplace_back("std::filesystem");
    KeyWords.emplace_back("std::filesystem::path");
    KeyWords.emplace_back("std::filesystem::directory_entry");
    KeyWords.emplace_back("std::filesystem::directory_iterator");
    KeyWords.emplace_back("std::filesystem::recursive_directory_iterator");
    KeyWords.emplace_back("std::filesystem::file_status");
    KeyWords.emplace_back("std::filesystem::file_type");
    KeyWords.emplace_back("std::filesystem::perms");

    // ==================== File and directory operations ====================
    KeyWords.emplace_back("std::filesystem::exists");
    KeyWords.emplace_back("std::filesystem::is_empty");
    KeyWords.emplace_back("std::filesystem::is_directory");
    KeyWords.emplace_back("std::filesystem::is_regular_file");
    KeyWords.emplace_back("std::filesystem::is_symlink");
    KeyWords.emplace_back("std::filesystem::create_directory");
    KeyWords.emplace_back("std::filesystem::create_directories");
    KeyWords.emplace_back("std::filesystem::remove");
    KeyWords.emplace_back("std::filesystem::remove_all");
    KeyWords.emplace_back("std::filesystem::rename");
    KeyWords.emplace_back("std::filesystem::copy");
    KeyWords.emplace_back("std::filesystem::copy_file");
    KeyWords.emplace_back("std::filesystem::current_path");
    KeyWords.emplace_back("std::filesystem::absolute");
    KeyWords.emplace_back("std::filesystem::canonical");
    KeyWords.emplace_back("std::filesystem::weakly_canonical");
    KeyWords.emplace_back("std::filesystem::relative");
    KeyWords.emplace_back("std::filesystem::proximate");
    KeyWords.emplace_back("std::filesystem::file_size");
    KeyWords.emplace_back("std::filesystem::last_write_time");
    KeyWords.emplace_back("std::filesystem::permissions");
    KeyWords.emplace_back("std::filesystem::space");
    KeyWords.emplace_back("std::filesystem::temp_directory_path");
    KeyWords.emplace_back("std::filesystem::read_symlink");
    KeyWords.emplace_back("std::filesystem::create_symlink");
    KeyWords.emplace_back("std::filesystem::create_hard_link");

    // ==================== Path operations ====================
    KeyWords.emplace_back("std::filesystem::path::append");
    KeyWords.emplace_back("std::filesystem::path::concat");
    KeyWords.emplace_back("std::filesystem::path::clear");
    KeyWords.emplace_back("std::filesystem::path::empty");
    KeyWords.emplace_back("std::filesystem::path::filename");
    KeyWords.emplace_back("std::filesystem::path::parent_path");
    KeyWords.emplace_back("std::filesystem::path::extension");
    KeyWords.emplace_back("std::filesystem::path::stem");
    KeyWords.emplace_back("std::filesystem::path::root_name");
    KeyWords.emplace_back("std::filesystem::path::root_directory");
    KeyWords.emplace_back("std::filesystem::path::root_path");
    KeyWords.emplace_back("std::filesystem::path::relative_path");
    KeyWords.emplace_back("std::filesystem::path::replace_extension");
    KeyWords.emplace_back("std::filesystem::path::has_filename");
    KeyWords.emplace_back("std::filesystem::path::has_parent_path");
    // ==================== Threads ====================
    KeyWords.emplace_back("std::thread");
    KeyWords.emplace_back("std::jthread");
    KeyWords.emplace_back("std::this_thread");
    KeyWords.emplace_back("std::this_thread::get_id");
    KeyWords.emplace_back("std::this_thread::sleep_for");
    KeyWords.emplace_back("std::this_thread::sleep_until");
    KeyWords.emplace_back("std::this_thread::yield");
    KeyWords.emplace_back("std::thread::id");

    // ==================== Mutexes ====================
    KeyWords.emplace_back("std::mutex");
    KeyWords.emplace_back("std::recursive_mutex");
    KeyWords.emplace_back("std::timed_mutex");
    KeyWords.emplace_back("std::recursive_timed_mutex");
    KeyWords.emplace_back("std::shared_mutex");
    KeyWords.emplace_back("std::shared_timed_mutex");
    KeyWords.emplace_back("std::lock_guard");
    KeyWords.emplace_back("std::unique_lock");
    KeyWords.emplace_back("std::shared_lock");
    KeyWords.emplace_back("std::scoped_lock");

    // ==================== Condition variables ====================
    KeyWords.emplace_back("std::condition_variable");
    KeyWords.emplace_back("std::condition_variable_any");
    KeyWords.emplace_back("std::notify_all_at_thread_exit");

    // ==================== Atomic operations ====================
    KeyWords.emplace_back("std::atomic");
    KeyWords.emplace_back("std::atomic_flag");
    KeyWords.emplace_back("std::atomic_ref");
    KeyWords.emplace_back("std::memory_order");
    KeyWords.emplace_back("std::memory_order_relaxed");
    KeyWords.emplace_back("std::memory_order_consume");
    KeyWords.emplace_back("std::memory_order_acquire");
    KeyWords.emplace_back("std::memory_order_release");
    KeyWords.emplace_back("std::memory_order_acq_rel");
    KeyWords.emplace_back("std::memory_order_seq_cst");
    KeyWords.emplace_back("std::atomic_thread_fence");
    KeyWords.emplace_back("std::atomic_signal_fence");

    // ==================== Futures and tasks ====================
    KeyWords.emplace_back("std::future");
    KeyWords.emplace_back("std::shared_future");
    KeyWords.emplace_back("std::promise");
    KeyWords.emplace_back("std::packaged_task");
    KeyWords.emplace_back("std::async");
    KeyWords.emplace_back("std::launch");
    KeyWords.emplace_back("std::future_status");
    KeyWords.emplace_back("std::future_error");
    KeyWords.emplace_back("std::stop_token");
    KeyWords.emplace_back("std::stop_source");
    KeyWords.emplace_back("std::stop_callback");
    KeyWords.emplace_back("std::latch");
    KeyWords.emplace_back("std::barrier");
    KeyWords.emplace_back("std::counting_semaphore");
    KeyWords.emplace_back("std::binary_semaphore");

    // ==================== Synchronization utilities ====================
    KeyWords.emplace_back("std::call_once");
    KeyWords.emplace_back("std::once_flag");
    KeyWords.emplace_back("std::atomic_wait");
    KeyWords.emplace_back("std::atomic_notify_one");
    KeyWords.emplace_back("std::atomic_notify_all");
    // ==================== Standard exceptions ====================
    KeyWords.emplace_back("std::exception");
    KeyWords.emplace_back("std::runtime_error");
    KeyWords.emplace_back("std::logic_error");
    KeyWords.emplace_back("std::invalid_argument");
    KeyWords.emplace_back("std::domain_error");
    KeyWords.emplace_back("std::length_error");
    KeyWords.emplace_back("std::out_of_range");
    KeyWords.emplace_back("std::range_error");
    KeyWords.emplace_back("std::overflow_error");
    KeyWords.emplace_back("std::underflow_error");
    KeyWords.emplace_back("std::bad_alloc");
    KeyWords.emplace_back("std::bad_array_new_length");
    KeyWords.emplace_back("std::bad_cast");
    KeyWords.emplace_back("std::bad_typeid");
    KeyWords.emplace_back("std::bad_exception");
    KeyWords.emplace_back("std::bad_function_call");
    KeyWords.emplace_back("std::bad_optional_access");
    KeyWords.emplace_back("std::bad_variant_access");
    KeyWords.emplace_back("std::bad_any_cast");
    KeyWords.emplace_back("std::system_error");
    KeyWords.emplace_back("std::filesystem::filesystem_error");

    // ==================== Error handling utilities ====================
    KeyWords.emplace_back("std::error_code");
    KeyWords.emplace_back("std::error_condition");
    KeyWords.emplace_back("std::error_category");
    KeyWords.emplace_back("std::generic_category");
    KeyWords.emplace_back("std::system_category");
    KeyWords.emplace_back("std::current_exception");
    KeyWords.emplace_back("std::rethrow_exception");
    KeyWords.emplace_back("std::make_exception_ptr");
    KeyWords.emplace_back("std::exception_ptr");
    KeyWords.emplace_back("std::nested_exception");
    KeyWords.emplace_back("std::throw_with_nested");
    KeyWords.emplace_back("std::rethrow_if_nested");

    // ==================== Assertions and debugging ====================
    KeyWords.emplace_back("assert");
    KeyWords.emplace_back("static_assert");
    KeyWords.emplace_back("std::source_location");
    KeyWords.emplace_back("std::stacktrace");
    KeyWords.emplace_back("std::stacktrace_entry");
    KeyWords.emplace_back("std::abort");
    KeyWords.emplace_back("std::terminate");
    KeyWords.emplace_back("std::set_terminate");
    KeyWords.emplace_back("std::quick_exit");
    KeyWords.emplace_back("std::exit");
    KeyWords.emplace_back("std::atexit");
    KeyWords.emplace_back("std::errno");
    // ==================== Type traits ====================
    KeyWords.emplace_back("std::is_same");
    KeyWords.emplace_back("std::is_same_v");
    KeyWords.emplace_back("std::is_integral");
    KeyWords.emplace_back("std::is_integral_v");
    KeyWords.emplace_back("std::is_floating_point");
    KeyWords.emplace_back("std::is_floating_point_v");
    KeyWords.emplace_back("std::is_arithmetic");
    KeyWords.emplace_back("std::is_arithmetic_v");
    KeyWords.emplace_back("std::is_pointer");
    KeyWords.emplace_back("std::is_pointer_v");
    KeyWords.emplace_back("std::is_reference");
    KeyWords.emplace_back("std::is_reference_v");
    KeyWords.emplace_back("std::is_const");
    KeyWords.emplace_back("std::is_const_v");
    KeyWords.emplace_back("std::is_volatile");
    KeyWords.emplace_back("std::is_volatile_v");
    KeyWords.emplace_back("std::is_array");
    KeyWords.emplace_back("std::is_array_v");
    KeyWords.emplace_back("std::is_enum");
    KeyWords.emplace_back("std::is_enum_v");
    KeyWords.emplace_back("std::is_class");
    KeyWords.emplace_back("std::is_class_v");
    KeyWords.emplace_back("std::is_base_of");
    KeyWords.emplace_back("std::is_base_of_v");
    KeyWords.emplace_back("std::is_convertible");
    KeyWords.emplace_back("std::is_convertible_v");
    KeyWords.emplace_back("std::is_constructible");
    KeyWords.emplace_back("std::is_constructible_v");
    KeyWords.emplace_back("std::is_default_constructible");
    KeyWords.emplace_back("std::is_default_constructible_v");
    KeyWords.emplace_back("std::is_copy_constructible");
    KeyWords.emplace_back("std::is_copy_constructible_v");
    KeyWords.emplace_back("std::is_move_constructible");
    KeyWords.emplace_back("std::is_move_constructible_v");
    KeyWords.emplace_back("std::is_trivially_copyable");
    KeyWords.emplace_back("std::is_trivially_copyable_v");
    KeyWords.emplace_back("std::is_standard_layout");
    KeyWords.emplace_back("std::is_standard_layout_v");

    // ==================== Type transformations ====================
    KeyWords.emplace_back("std::remove_const");
    KeyWords.emplace_back("std::remove_const_t");
    KeyWords.emplace_back("std::remove_volatile");
    KeyWords.emplace_back("std::remove_volatile_t");
    KeyWords.emplace_back("std::remove_cv");
    KeyWords.emplace_back("std::remove_cv_t");
    KeyWords.emplace_back("std::remove_reference");
    KeyWords.emplace_back("std::remove_reference_t");
    KeyWords.emplace_back("std::remove_pointer");
    KeyWords.emplace_back("std::remove_pointer_t");
    KeyWords.emplace_back("std::decay");
    KeyWords.emplace_back("std::decay_t");
    KeyWords.emplace_back("std::enable_if");
    KeyWords.emplace_back("std::enable_if_t");
    KeyWords.emplace_back("std::conditional");
    KeyWords.emplace_back("std::conditional_t");
    KeyWords.emplace_back("std::common_type");
    KeyWords.emplace_back("std::common_type_t");
    KeyWords.emplace_back("std::common_reference");
    KeyWords.emplace_back("std::common_reference_t");
    KeyWords.emplace_back("std::underlying_type");
    KeyWords.emplace_back("std::underlying_type_t");
    KeyWords.emplace_back("std::invoke_result");
    KeyWords.emplace_back("std::invoke_result_t");
    KeyWords.emplace_back("std::result_of");
    KeyWords.emplace_back("std::result_of_t");
    KeyWords.emplace_back("std::void_t");
    KeyWords.emplace_back("std::type_identity");
    KeyWords.emplace_back("std::type_identity_t");

    // ==================== Concepts ====================
    KeyWords.emplace_back("std::same_as");
    KeyWords.emplace_back("std::derived_from");
    KeyWords.emplace_back("std::convertible_to");
    KeyWords.emplace_back("std::common_reference_with");
    KeyWords.emplace_back("std::common_with");
    KeyWords.emplace_back("std::integral");
    KeyWords.emplace_back("std::signed_integral");
    KeyWords.emplace_back("std::unsigned_integral");
    KeyWords.emplace_back("std::floating_point");
    KeyWords.emplace_back("std::assignable_from");
    KeyWords.emplace_back("std::default_initializable");
    KeyWords.emplace_back("std::move_constructible");
    KeyWords.emplace_back("std::copy_constructible");
    KeyWords.emplace_back("std::swappable");
    KeyWords.emplace_back("std::destructible");
    KeyWords.emplace_back("std::constructible_from");
    KeyWords.emplace_back("std::invocable");
    KeyWords.emplace_back("std::regular_invocable");
    KeyWords.emplace_back("std::predicate");
    KeyWords.emplace_back("std::relation");
    KeyWords.emplace_back("std::strict_weak_order");
    KeyWords.emplace_back("std::equality_comparable");
    KeyWords.emplace_back("std::totally_ordered");
    KeyWords.emplace_back("std::ranges::range");
    KeyWords.emplace_back("std::ranges::input_range");
    KeyWords.emplace_back("std::ranges::forward_range");
    KeyWords.emplace_back("std::ranges::bidirectional_range");
    KeyWords.emplace_back("std::ranges::random_access_range");
    KeyWords.emplace_back("std::ranges::contiguous_range");
    KeyWords.emplace_back("std::ranges::sized_range");
    // ==================== Iterator utilities ====================
    KeyWords.emplace_back("std::begin");
    KeyWords.emplace_back("std::end");
    KeyWords.emplace_back("std::cbegin");
    KeyWords.emplace_back("std::cend");
    KeyWords.emplace_back("std::rbegin");
    KeyWords.emplace_back("std::rend");
    KeyWords.emplace_back("std::crbegin");
    KeyWords.emplace_back("std::crend");
    KeyWords.emplace_back("std::size");
    KeyWords.emplace_back("std::ssize");
    KeyWords.emplace_back("std::empty");
    KeyWords.emplace_back("std::data");
    KeyWords.emplace_back("std::distance");
    KeyWords.emplace_back("std::advance");
    KeyWords.emplace_back("std::next");
    KeyWords.emplace_back("std::prev");
    KeyWords.emplace_back("std::iter_move");
    KeyWords.emplace_back("std::iter_swap");
    KeyWords.emplace_back("std::reverse_iterator");
    KeyWords.emplace_back("std::move_iterator");
    KeyWords.emplace_back("std::counted_iterator");
    KeyWords.emplace_back("std::common_iterator");
    KeyWords.emplace_back("std::istream_iterator");
    KeyWords.emplace_back("std::ostream_iterator");
    KeyWords.emplace_back("std::back_insert_iterator");
    KeyWords.emplace_back("std::front_insert_iterator");
    KeyWords.emplace_back("std::insert_iterator");
    KeyWords.emplace_back("std::back_inserter");
    KeyWords.emplace_back("std::front_inserter");
    KeyWords.emplace_back("std::inserter");

    // ==================== Common container member functions ====================
    KeyWords.emplace_back("begin");
    KeyWords.emplace_back("end");
    KeyWords.emplace_back("cbegin");
    KeyWords.emplace_back("cend");
    KeyWords.emplace_back("rbegin");
    KeyWords.emplace_back("rend");
    KeyWords.emplace_back("empty");
    KeyWords.emplace_back("size");
    KeyWords.emplace_back("max_size");
    KeyWords.emplace_back("data");
    KeyWords.emplace_back("at");
    KeyWords.emplace_back("front");
    KeyWords.emplace_back("back");
    KeyWords.emplace_back("clear");
    KeyWords.emplace_back("insert");
    KeyWords.emplace_back("insert_range");
    KeyWords.emplace_back("emplace");
    KeyWords.emplace_back("erase");
    KeyWords.emplace_back("swap");
    KeyWords.emplace_back("contains");
    KeyWords.emplace_back("find");
    KeyWords.emplace_back("count");
    KeyWords.emplace_back("equal_range");
    KeyWords.emplace_back("lower_bound");
    KeyWords.emplace_back("upper_bound");

    // ==================== Sequence container members ====================
    KeyWords.emplace_back("push_back");
    KeyWords.emplace_back("emplace_back");
    KeyWords.emplace_back("pop_back");
    KeyWords.emplace_back("push_front");
    KeyWords.emplace_back("emplace_front");
    KeyWords.emplace_back("pop_front");
    KeyWords.emplace_back("resize");
    KeyWords.emplace_back("reserve");
    KeyWords.emplace_back("capacity");
    KeyWords.emplace_back("shrink_to_fit");
    KeyWords.emplace_back("assign");
    KeyWords.emplace_back("assign_range");
    KeyWords.emplace_back("append_range");

    // ==================== Associative container members ====================
    KeyWords.emplace_back("try_emplace");
    KeyWords.emplace_back("insert_or_assign");
    KeyWords.emplace_back("extract");
    KeyWords.emplace_back("merge");
    KeyWords.emplace_back("key_comp");
    KeyWords.emplace_back("value_comp");
    KeyWords.emplace_back("bucket_count");
    KeyWords.emplace_back("load_factor");
    KeyWords.emplace_back("max_load_factor");
    KeyWords.emplace_back("rehash");
    KeyWords.emplace_back("reserve");

    // ==================== Stack, queue and priority queue members ====================
    KeyWords.emplace_back("top");
    KeyWords.emplace_back("push");
    KeyWords.emplace_back("emplace");
    KeyWords.emplace_back("pop");
    KeyWords.emplace_back("front");
    KeyWords.emplace_back("back");
    KeyWords.emplace_back("priority_queue");
    KeyWords.emplace_back("queue");
    KeyWords.emplace_back("stack");
    // ==================== Bit operations ====================
    KeyWords.emplace_back("std::bitset");
    KeyWords.emplace_back("std::bit_cast");
    KeyWords.emplace_back("std::bit_width");
    KeyWords.emplace_back("std::bit_floor");
    KeyWords.emplace_back("std::bit_ceil");
    KeyWords.emplace_back("std::has_single_bit");
    KeyWords.emplace_back("std::popcount");
    KeyWords.emplace_back("std::countl_zero");
    KeyWords.emplace_back("std::countl_one");
    KeyWords.emplace_back("std::countr_zero");
    KeyWords.emplace_back("std::countr_one");
    KeyWords.emplace_back("std::rotl");
    KeyWords.emplace_back("std::rotr");

    // ==================== Type information ====================
    KeyWords.emplace_back("std::type_info");
    KeyWords.emplace_back("std::type_index");
    KeyWords.emplace_back("std::typeid");
    KeyWords.emplace_back("std::bad_cast");
    KeyWords.emplace_back("std::bad_typeid");

    // ==================== Coroutines ====================
    KeyWords.emplace_back("std::coroutine_handle");
    KeyWords.emplace_back("std::coroutine_traits");
    KeyWords.emplace_back("std::suspend_never");
    KeyWords.emplace_back("std::suspend_always");
    KeyWords.emplace_back("std::noop_coroutine");
    KeyWords.emplace_back("std::generator");

    // ==================== Execution and parallel algorithms ====================
    KeyWords.emplace_back("std::execution");
    KeyWords.emplace_back("std::execution::seq");
    KeyWords.emplace_back("std::execution::par");
    KeyWords.emplace_back("std::execution::par_unseq");
    KeyWords.emplace_back("std::execution::unseq");

    // ==================== C++23 / C++26 additions ====================
    KeyWords.emplace_back("std::expected");
    KeyWords.emplace_back("std::unexpected");
    KeyWords.emplace_back("std::unreachable");
    KeyWords.emplace_back("std::println");
    KeyWords.emplace_back("std::print");
    KeyWords.emplace_back("std::stacktrace");
    KeyWords.emplace_back("std::stacktrace_entry");
    KeyWords.emplace_back("std::generator");
    KeyWords.emplace_back("std::inplace_vector");
    KeyWords.emplace_back("std::hive");
    KeyWords.emplace_back("std::text_encoding");
    KeyWords.emplace_back("std::simd");
    KeyWords.emplace_back("std::linalg");
    // ==================== Common macros ====================
    KeyWords.emplace_back("NULL");
    KeyWords.emplace_back("EOF");
    KeyWords.emplace_back("EXIT_SUCCESS");
    KeyWords.emplace_back("EXIT_FAILURE");
    KeyWords.emplace_back("INT_MAX");
    KeyWords.emplace_back("INT_MIN");
    KeyWords.emplace_back("UINT_MAX");
    KeyWords.emplace_back("CHAR_BIT");
    KeyWords.emplace_back("FLT_MAX");
    KeyWords.emplace_back("DBL_MAX");
    KeyWords.emplace_back("RAND_MAX");

    // ==================== Common C library functions ====================
    KeyWords.emplace_back("printf");
    KeyWords.emplace_back("fprintf");
    KeyWords.emplace_back("sprintf");
    KeyWords.emplace_back("snprintf");
    KeyWords.emplace_back("scanf");
    KeyWords.emplace_back("fscanf");
    KeyWords.emplace_back("sscanf");
    KeyWords.emplace_back("malloc");
    KeyWords.emplace_back("calloc");
    KeyWords.emplace_back("realloc");
    KeyWords.emplace_back("free");
    KeyWords.emplace_back("exit");
    KeyWords.emplace_back("abort");
    KeyWords.emplace_back("getchar");
    KeyWords.emplace_back("putchar");
    KeyWords.emplace_back("fopen");
    KeyWords.emplace_back("fclose");
    KeyWords.emplace_back("fread");
    KeyWords.emplace_back("fwrite");
    KeyWords.emplace_back("rand");
    KeyWords.emplace_back("srand");
    KeyWords.emplace_back("qsort");
    KeyWords.emplace_back("bsearch");

    // ==================== Common C++ aliases and types ====================
    KeyWords.emplace_back("size_t");
    KeyWords.emplace_back("ptrdiff_t");
    KeyWords.emplace_back("intptr_t");
    KeyWords.emplace_back("uintptr_t");
    KeyWords.emplace_back("int8_t");
    KeyWords.emplace_back("int16_t");
    KeyWords.emplace_back("int32_t");
    KeyWords.emplace_back("int64_t");
    KeyWords.emplace_back("uint8_t");
    KeyWords.emplace_back("uint16_t");
    KeyWords.emplace_back("uint32_t");
    KeyWords.emplace_back("uint64_t");

    // ==================== Common coding terms ====================
    KeyWords.emplace_back("nullptr_t");
    KeyWords.emplace_back("string");
    KeyWords.emplace_back("vector");
    KeyWords.emplace_back("map");
    KeyWords.emplace_back("set");
    KeyWords.emplace_back("list");
    KeyWords.emplace_back("iterator");
    KeyWords.emplace_back("const_iterator");
    KeyWords.emplace_back("value_type");
    KeyWords.emplace_back("key_type");
    KeyWords.emplace_back("mapped_type");
    KeyWords.emplace_back("size_type");
    KeyWords.emplace_back("difference_type");
    KeyWords.emplace_back("reference");
    KeyWords.emplace_back("const_reference");
    KeyWords.emplace_back("pointer");
    KeyWords.emplace_back("const_pointer");
    KeyWords.emplace_back("allocator_type");
}

std::vector<std::string> LDDrift::CodePathfinder::GetCodeSuggestions(
    const std::string& CodeSuggestion) {
    // Return cached results if the query has not changed.
    if (CodeSuggestion == lastQuery) {
        return lastSuggestions;
    }

    lastQuery = CodeSuggestion;
    lastSuggestions.clear();

    // Do not calculate a score for an empty query.
    if (CodeSuggestion.empty()) {
        return lastSuggestions;
    }

    std::vector<std::pair<std::string, float>> RankedCodeSuggestions;
    RankedCodeSuggestions.reserve(KeyWords.size());

    std::unordered_set<std::string> SeenKeywords;

    for (const std::string& keyWord : KeyWords) {
        // Prevent duplicate suggestions.
        if (!SeenKeywords.emplace(keyWord).second) {
            continue;
        }

        float suggestionConfidence = 0.0f;

        // 1. Direct substring match gets priority.

        if (const std::size_t substringPosition = keyWord.find(CodeSuggestion);
            substringPosition != std::string::npos) {
            suggestionConfidence =
                2.0f + 1.0f / static_cast<float>(substringPosition + 1);
        } else {
            // 2. Fuzzy matching: query characters must appear in order.
            std::size_t queryIndex = 0;
            std::size_t firstMatchPosition = std::string::npos;
            std::size_t lastMatchPosition = 0;

            for (std::size_t i = 0;
                 i < keyWord.size() && queryIndex < CodeSuggestion.size();
                 ++i) {
                if (keyWord[i] == CodeSuggestion[queryIndex]) {
                    if (firstMatchPosition == std::string::npos) {
                        firstMatchPosition = i;
                    }

                    lastMatchPosition = i;
                    ++queryIndex;
                }
            }

            const float matchRatio =
                static_cast<float>(queryIndex) /
                static_cast<float>(CodeSuggestion.size());

            float compactness = 0.0f;

            if (queryIndex > 0) {
                const std::size_t matchedSpan =
                    lastMatchPosition - firstMatchPosition + 1;

                compactness =
                    static_cast<float>(queryIndex) /
                    static_cast<float>(matchedSpan);
            }

            suggestionConfidence =
                0.8f * matchRatio + 0.2f * compactness;

            // Ignore weak fuzzy matches.
            if (suggestionConfidence <= 0.9f) {
                continue;
            }
        }

        RankedCodeSuggestions.emplace_back(
            keyWord,
            suggestionConfidence);
    }

    // 3. Sort by score, highest first.
    std::ranges::sort(
        RankedCodeSuggestions,
        [](const auto& a, const auto& b)
        {
            if (a.second != b.second) {
                return a.second > b.second;
            }

            // Deterministic order when scores are equal.
            return a.first < b.first;
        });

    // 4. Extract the sorted keywords.
    lastSuggestions.reserve(RankedCodeSuggestions.size());

    for (const auto& keyword : RankedCodeSuggestions | std::views::keys) {
        lastSuggestions.emplace_back(keyword);
    }

    return lastSuggestions;
}
