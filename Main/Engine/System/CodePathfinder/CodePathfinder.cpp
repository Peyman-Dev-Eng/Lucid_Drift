#include "CodePathfinder.h"

#include <memory>
LDDrift::CodePathfinder::CodePathfinder() = default;

LDDrift::CodePathfinder::~CodePathfinder() = default;

void LDDrift::CodePathfinder::initializeCodePathfinder() {
    std_keyWords.reserve(1200);

    // ==================== Sequence containers ====================
    std_keyWords.emplace_back("std::array");
    std_keyWords.emplace_back("std::vector");
    std_keyWords.emplace_back("std::deque");
    std_keyWords.emplace_back("std::list");
    std_keyWords.emplace_back("std::forward_list");
    std_keyWords.emplace_back("std::inplace_vector"); // C++26

    // ==================== Associative containers ====================
    std_keyWords.emplace_back("std::set");
    std_keyWords.emplace_back("std::multiset");
    std_keyWords.emplace_back("std::map");
    std_keyWords.emplace_back("std::multimap");

    // ==================== Unordered containers ====================
    std_keyWords.emplace_back("std::unordered_set");
    std_keyWords.emplace_back("std::unordered_multiset");
    std_keyWords.emplace_back("std::unordered_map");
    std_keyWords.emplace_back("std::unordered_multimap");

    // ==================== Container adaptors ====================
    std_keyWords.emplace_back("std::stack");
    std_keyWords.emplace_back("std::queue");
    std_keyWords.emplace_back("std::priority_queue");

    // ==================== C++23 / C++26 containers ====================
    std_keyWords.emplace_back("std::flat_map"); // C++23
    std_keyWords.emplace_back("std::flat_multimap"); // C++23
    std_keyWords.emplace_back("std::flat_set"); // C++23
    std_keyWords.emplace_back("std::flat_multiset"); // C++23
    std_keyWords.emplace_back("std::hive"); // C++26

    // ==================== Views and non-owning sequences ====================
    std_keyWords.emplace_back("std::span");
    std_keyWords.emplace_back("std::mdspan");
    std_keyWords.emplace_back("std::string_view");
    std_keyWords.emplace_back("std::wstring_view");
    std_keyWords.emplace_back("std::u8string_view");
    std_keyWords.emplace_back("std::u16string_view");
    std_keyWords.emplace_back("std::u32string_view");

    // ==================== Strings ====================
    std_keyWords.emplace_back("std::string");
    std_keyWords.emplace_back("std::wstring");
    std_keyWords.emplace_back("std::u8string");
    std_keyWords.emplace_back("std::u16string");
    std_keyWords.emplace_back("std::u32string");
    std_keyWords.emplace_back("std::basic_string");

    // ==================== Pairs, tuples and aggregates ====================
    std_keyWords.emplace_back("std::pair");
    std_keyWords.emplace_back("std::tuple");
    std_keyWords.emplace_back("std::array");
    std_keyWords.emplace_back("std::initializer_list");
    std_keyWords.emplace_back("std::optional");
    std_keyWords.emplace_back("std::variant");
    std_keyWords.emplace_back("std::any");
    std_keyWords.emplace_back("std::expected");
    std_keyWords.emplace_back("std::bitset");
    std_keyWords.emplace_back("std::valarray");

    // ==================== Complex numbers ====================
    std_keyWords.emplace_back("std::complex");
    std_keyWords.emplace_back("std::numbers");
    // ==================== Smart pointers ====================
    std_keyWords.emplace_back("std::unique_ptr");
    std_keyWords.emplace_back("std::shared_ptr");
    std_keyWords.emplace_back("std::weak_ptr");
    std_keyWords.emplace_back("std::auto_ptr"); // منسوخ و حذف‌شده در استانداردهای جدید

    // ==================== Smart pointer creation ====================
    std_keyWords.emplace_back("std::make_unique");
    std_keyWords.emplace_back("std::make_shared");
    std_keyWords.emplace_back("std::allocate_shared");
    std_keyWords.emplace_back("std::make_unique_for_overwrite");
    std_keyWords.emplace_back("std::make_shared_for_overwrite");

    // ==================== Memory utilities ====================
    std_keyWords.emplace_back("std::allocator");
    std_keyWords.emplace_back("std::allocator_traits");
    std_keyWords.emplace_back("std::addressof");
    std_keyWords.emplace_back("std::construct_at");
    std_keyWords.emplace_back("std::destroy_at");
    std_keyWords.emplace_back("std::destroy");
    std_keyWords.emplace_back("std::destroy_n");
    std_keyWords.emplace_back("std::align");
    std_keyWords.emplace_back("std::assume_aligned");

    // ==================== Pointer helpers ====================
    std_keyWords.emplace_back("std::to_address");
    std_keyWords.emplace_back("std::pointer_traits");
    std_keyWords.emplace_back("std::owner_less");
    std_keyWords.emplace_back("std::get_deleter");

    // ==================== Resource management ====================
    std_keyWords.emplace_back("std::unique_lock");
    std_keyWords.emplace_back("std::shared_lock");
    std_keyWords.emplace_back("std::lock_guard");
    std_keyWords.emplace_back("std::scoped_lock");
    std_keyWords.emplace_back("std::jthread");
    std_keyWords.emplace_back("std::lock");
    std_keyWords.emplace_back("std::try_lock");
    std_keyWords.emplace_back("std::unlock");
    // ==================== Move and forwarding ====================
    std_keyWords.emplace_back("std::move");
    std_keyWords.emplace_back("std::forward");
    std_keyWords.emplace_back("std::move_if_noexcept");
    std_keyWords.emplace_back("std::forward_like");
    std_keyWords.emplace_back("std::exchange");
    std_keyWords.emplace_back("std::swap");
    std_keyWords.emplace_back("std::swap_ranges");

    // ==================== Pair and tuple utilities ====================
    std_keyWords.emplace_back("std::make_pair");
    std_keyWords.emplace_back("std::make_tuple");
    std_keyWords.emplace_back("std::tie");
    std_keyWords.emplace_back("std::forward_as_tuple");
    std_keyWords.emplace_back("std::apply");
    std_keyWords.emplace_back("std::make_from_tuple");
    std_keyWords.emplace_back("std::get");
    std_keyWords.emplace_back("std::tuple_size");
    std_keyWords.emplace_back("std::tuple_element");

    // ==================== Common utility functions ====================
    std_keyWords.emplace_back("std::min");
    std_keyWords.emplace_back("std::max");
    std_keyWords.emplace_back("std::minmax");
    std_keyWords.emplace_back("std::clamp");
    std_keyWords.emplace_back("std::min_element");
    std_keyWords.emplace_back("std::max_element");
    std_keyWords.emplace_back("std::exchange");
    std_keyWords.emplace_back("std::as_const");
    std_keyWords.emplace_back("std::to_underlying");
    std_keyWords.emplace_back("std::cmp_equal");
    std_keyWords.emplace_back("std::cmp_not_equal");
    std_keyWords.emplace_back("std::cmp_less");
    std_keyWords.emplace_back("std::cmp_greater");
    std_keyWords.emplace_back("std::cmp_less_equal");
    std_keyWords.emplace_back("std::cmp_greater_equal");

    // ==================== Function objects and invocation ====================
    std_keyWords.emplace_back("std::function");
    std_keyWords.emplace_back("std::invoke");
    std_keyWords.emplace_back("std::invoke_result");
    std_keyWords.emplace_back("std::bind");
    std_keyWords.emplace_back("std::bind_front");
    std_keyWords.emplace_back("std::bind_back");
    std_keyWords.emplace_back("std::ref");
    std_keyWords.emplace_back("std::cref");
    std_keyWords.emplace_back("std::reference_wrapper");
    std_keyWords.emplace_back("std::mem_fn");
    std_keyWords.emplace_back("std::not_fn");
    std_keyWords.emplace_back("std::identity");

    // ==================== Common functional objects ====================
    std_keyWords.emplace_back("std::plus");
    std_keyWords.emplace_back("std::minus");
    std_keyWords.emplace_back("std::multiplies");
    std_keyWords.emplace_back("std::divides");
    std_keyWords.emplace_back("std::modulus");
    std_keyWords.emplace_back("std::negate");
    std_keyWords.emplace_back("std::equal_to");
    std_keyWords.emplace_back("std::not_equal_to");
    std_keyWords.emplace_back("std::greater");
    std_keyWords.emplace_back("std::greater_equal");
    std_keyWords.emplace_back("std::less");
    std_keyWords.emplace_back("std::less_equal");
    std_keyWords.emplace_back("std::logical_and");
    std_keyWords.emplace_back("std::logical_or");
    std_keyWords.emplace_back("std::logical_not");
    std_keyWords.emplace_back("std::bit_and");
    std_keyWords.emplace_back("std::bit_or");
    std_keyWords.emplace_back("std::bit_xor");
    std_keyWords.emplace_back("std::bit_not");
    // ==================== Sorting ====================
    std_keyWords.emplace_back("std::sort");
    std_keyWords.emplace_back("std::stable_sort");
    std_keyWords.emplace_back("std::partial_sort");
    std_keyWords.emplace_back("std::nth_element");
    std_keyWords.emplace_back("std::is_sorted");
    std_keyWords.emplace_back("std::is_sorted_until");
    std_keyWords.emplace_back("std::partial_sort_copy");

    // ==================== Searching ====================
    std_keyWords.emplace_back("std::find");
    std_keyWords.emplace_back("std::find_if");
    std_keyWords.emplace_back("std::find_if_not");
    std_keyWords.emplace_back("std::find_end");
    std_keyWords.emplace_back("std::find_first_of");
    std_keyWords.emplace_back("std::search");
    std_keyWords.emplace_back("std::search_n");
    std_keyWords.emplace_back("std::binary_search");
    std_keyWords.emplace_back("std::lower_bound");
    std_keyWords.emplace_back("std::upper_bound");
    std_keyWords.emplace_back("std::equal_range");

    // ==================== Counting and comparison ====================
    std_keyWords.emplace_back("std::count");
    std_keyWords.emplace_back("std::count_if");
    std_keyWords.emplace_back("std::all_of");
    std_keyWords.emplace_back("std::any_of");
    std_keyWords.emplace_back("std::none_of");
    std_keyWords.emplace_back("std::equal");
    std_keyWords.emplace_back("std::mismatch");
    std_keyWords.emplace_back("std::lexicographical_compare");
    std_keyWords.emplace_back("std::lexicographical_compare_three_way");

    // ==================== Transforming ====================
    std_keyWords.emplace_back("std::copy");
    std_keyWords.emplace_back("std::copy_if");
    std_keyWords.emplace_back("std::copy_n");
    std_keyWords.emplace_back("std::copy_backward");
    std_keyWords.emplace_back("std::move");
    std_keyWords.emplace_back("std::move_backward");
    std_keyWords.emplace_back("std::transform");
    std_keyWords.emplace_back("std::replace");
    std_keyWords.emplace_back("std::replace_if");
    std_keyWords.emplace_back("std::replace_copy");
    std_keyWords.emplace_back("std::replace_copy_if");
    std_keyWords.emplace_back("std::fill");
    std_keyWords.emplace_back("std::fill_n");
    std_keyWords.emplace_back("std::generate");
    std_keyWords.emplace_back("std::generate_n");
    std_keyWords.emplace_back("std::remove");
    std_keyWords.emplace_back("std::remove_if");
    std_keyWords.emplace_back("std::remove_copy");
    std_keyWords.emplace_back("std::remove_copy_if");
    std_keyWords.emplace_back("std::unique");
    std_keyWords.emplace_back("std::unique_copy");
    std_keyWords.emplace_back("std::reverse");
    std_keyWords.emplace_back("std::reverse_copy");
    std_keyWords.emplace_back("std::rotate");
    std_keyWords.emplace_back("std::rotate_copy");
    std_keyWords.emplace_back("std::shuffle");

    // ==================== Numeric algorithms ====================
    std_keyWords.emplace_back("std::accumulate");
    std_keyWords.emplace_back("std::reduce");
    std_keyWords.emplace_back("std::transform_reduce");
    std_keyWords.emplace_back("std::inner_product");
    std_keyWords.emplace_back("std::partial_sum");
    std_keyWords.emplace_back("std::inclusive_scan");
    std_keyWords.emplace_back("std::exclusive_scan");
    std_keyWords.emplace_back("std::adjacent_difference");
    std_keyWords.emplace_back("std::iota");
    std_keyWords.emplace_back("std::gcd");
    std_keyWords.emplace_back("std::lcm");

    // ==================== Set algorithms ====================
    std_keyWords.emplace_back("std::includes");
    std_keyWords.emplace_back("std::set_union");
    std_keyWords.emplace_back("std::set_intersection");
    std_keyWords.emplace_back("std::set_difference");
    std_keyWords.emplace_back("std::set_symmetric_difference");

    // ==================== Heap operations ====================
    std_keyWords.emplace_back("std::make_heap");
    std_keyWords.emplace_back("std::push_heap");
    std_keyWords.emplace_back("std::pop_heap");
    std_keyWords.emplace_back("std::sort_heap");
    std_keyWords.emplace_back("std::is_heap");
    std_keyWords.emplace_back("std::is_heap_until");

    // ==================== Permutations ====================
    std_keyWords.emplace_back("std::next_permutation");
    std_keyWords.emplace_back("std::prev_permutation");

    // ==================== Other algorithms ====================
    std_keyWords.emplace_back("std::for_each");
    std_keyWords.emplace_back("std::for_each_n");
    std_keyWords.emplace_back("std::iter_swap");
    std_keyWords.emplace_back("std::swap_ranges");
    std_keyWords.emplace_back("std::partition");
    std_keyWords.emplace_back("std::stable_partition");
    std_keyWords.emplace_back("std::partition_copy");
    std_keyWords.emplace_back("std::is_partitioned");
    std_keyWords.emplace_back("std::max_element");
    std_keyWords.emplace_back("std::min_element");
    std_keyWords.emplace_back("std::clamp");
    std_keyWords.emplace_back("std::sample");
    std_keyWords.emplace_back("std::invoke");
    // ==================== Ranges ====================
    std_keyWords.emplace_back("std::ranges");
    std_keyWords.emplace_back("std::ranges::begin");
    std_keyWords.emplace_back("std::ranges::end");
    std_keyWords.emplace_back("std::ranges::size");
    std_keyWords.emplace_back("std::ranges::empty");
    std_keyWords.emplace_back("std::ranges::data");
    std_keyWords.emplace_back("std::ranges::distance");
    std_keyWords.emplace_back("std::ranges::advance");
    std_keyWords.emplace_back("std::ranges::next");
    std_keyWords.emplace_back("std::ranges::prev");

    // ==================== Ranges algorithms ====================
    std_keyWords.emplace_back("std::ranges::sort");
    std_keyWords.emplace_back("std::ranges::find");
    std_keyWords.emplace_back("std::ranges::find_if");
    std_keyWords.emplace_back("std::ranges::count");
    std_keyWords.emplace_back("std::ranges::count_if");
    std_keyWords.emplace_back("std::ranges::copy");
    std_keyWords.emplace_back("std::ranges::transform");
    std_keyWords.emplace_back("std::ranges::for_each");
    std_keyWords.emplace_back("std::ranges::remove");
    std_keyWords.emplace_back("std::ranges::remove_if");
    std_keyWords.emplace_back("std::ranges::reverse");
    std_keyWords.emplace_back("std::ranges::unique");
    std_keyWords.emplace_back("std::ranges::partition");
    std_keyWords.emplace_back("std::ranges::lower_bound");
    std_keyWords.emplace_back("std::ranges::upper_bound");
    std_keyWords.emplace_back("std::ranges::binary_search");
    std_keyWords.emplace_back("std::ranges::all_of");
    std_keyWords.emplace_back("std::ranges::any_of");
    std_keyWords.emplace_back("std::ranges::none_of");

    // ==================== Range views ====================
    std_keyWords.emplace_back("std::views");
    std_keyWords.emplace_back("std::views::all");
    std_keyWords.emplace_back("std::views::filter");
    std_keyWords.emplace_back("std::views::transform");
    std_keyWords.emplace_back("std::views::take");
    std_keyWords.emplace_back("std::views::take_while");
    std_keyWords.emplace_back("std::views::drop");
    std_keyWords.emplace_back("std::views::drop_while");
    std_keyWords.emplace_back("std::views::iota");
    std_keyWords.emplace_back("std::views::join");
    std_keyWords.emplace_back("std::views::split");
    std_keyWords.emplace_back("std::views::reverse");
    std_keyWords.emplace_back("std::views::keys");
    std_keyWords.emplace_back("std::views::values");
    std_keyWords.emplace_back("std::views::enumerate");
    std_keyWords.emplace_back("std::views::zip");
    std_keyWords.emplace_back("std::views::zip_transform");
    std_keyWords.emplace_back("std::views::adjacent");
    std_keyWords.emplace_back("std::views::chunk");
    std_keyWords.emplace_back("std::views::stride");
    std_keyWords.emplace_back("std::views::repeat");
    std_keyWords.emplace_back("std::views::cartesian_product");
    // ==================== String operations ====================
    std_keyWords.emplace_back("std::to_string");
    std_keyWords.emplace_back("std::to_wstring");
    std_keyWords.emplace_back("std::stoi");
    std_keyWords.emplace_back("std::stol");
    std_keyWords.emplace_back("std::stoll");
    std_keyWords.emplace_back("std::stoul");
    std_keyWords.emplace_back("std::stoull");
    std_keyWords.emplace_back("std::stof");
    std_keyWords.emplace_back("std::stod");
    std_keyWords.emplace_back("std::stold");

    // ==================== Character handling ====================
    std_keyWords.emplace_back("std::isalnum");
    std_keyWords.emplace_back("std::isalpha");
    std_keyWords.emplace_back("std::isdigit");
    std_keyWords.emplace_back("std::islower");
    std_keyWords.emplace_back("std::isupper");
    std_keyWords.emplace_back("std::isspace");
    std_keyWords.emplace_back("std::isprint");
    std_keyWords.emplace_back("std::ispunct");
    std_keyWords.emplace_back("std::isxdigit");
    std_keyWords.emplace_back("std::tolower");
    std_keyWords.emplace_back("std::toupper");

    // ==================== C-style string handling ====================
    std_keyWords.emplace_back("std::strlen");
    std_keyWords.emplace_back("std::strcmp");
    std_keyWords.emplace_back("std::strncmp");
    std_keyWords.emplace_back("std::strcpy");
    std_keyWords.emplace_back("std::strncpy");
    std_keyWords.emplace_back("std::strcat");
    std_keyWords.emplace_back("std::strncat");
    std_keyWords.emplace_back("std::strstr");
    std_keyWords.emplace_back("std::strchr");
    std_keyWords.emplace_back("std::strrchr");
    std_keyWords.emplace_back("std::strtok");
    std_keyWords.emplace_back("std::memcpy");
    std_keyWords.emplace_back("std::memmove");
    std_keyWords.emplace_back("std::memset");
    std_keyWords.emplace_back("std::memcmp");
    std_keyWords.emplace_back("std::memchr");

    // ==================== String formatting ====================
    std_keyWords.emplace_back("std::format");
    std_keyWords.emplace_back("std::format_to");
    std_keyWords.emplace_back("std::format_to_n");
    std_keyWords.emplace_back("std::formatted_size");
    std_keyWords.emplace_back("std::vformat");
    std_keyWords.emplace_back("std::print");
    std_keyWords.emplace_back("std::println");

    // ==================== String views and spans ====================
    std_keyWords.emplace_back("std::string_view");
    std_keyWords.emplace_back("std::span");
    std_keyWords.emplace_back("std::subrange");

    // ==================== Regular expressions ====================
    std_keyWords.emplace_back("std::regex");
    std_keyWords.emplace_back("std::regex_match");
    std_keyWords.emplace_back("std::regex_search");
    std_keyWords.emplace_back("std::regex_replace");
    std_keyWords.emplace_back("std::regex_iterator");
    std_keyWords.emplace_back("std::smatch");
    std_keyWords.emplace_back("std::cmatch");
    std_keyWords.emplace_back("std::match_results");
    std_keyWords.emplace_back("std::regex_error");
    // ==================== Standard streams ====================
    std_keyWords.emplace_back("std::cin");
    std_keyWords.emplace_back("std::cout");
    std_keyWords.emplace_back("std::cerr");
    std_keyWords.emplace_back("std::clog");
    std_keyWords.emplace_back("std::wcin");
    std_keyWords.emplace_back("std::wcout");
    std_keyWords.emplace_back("std::wcerr");
    std_keyWords.emplace_back("std::wclog");

    // ==================== Stream classes ====================
    std_keyWords.emplace_back("std::istream");
    std_keyWords.emplace_back("std::ostream");
    std_keyWords.emplace_back("std::iostream");
    std_keyWords.emplace_back("std::ifstream");
    std_keyWords.emplace_back("std::ofstream");
    std_keyWords.emplace_back("std::fstream");
    std_keyWords.emplace_back("std::istringstream");
    std_keyWords.emplace_back("std::ostringstream");
    std_keyWords.emplace_back("std::stringstream");
    std_keyWords.emplace_back("std::streambuf");
    std_keyWords.emplace_back("std::filebuf");

    // ==================== Stream manipulators ====================
    std_keyWords.emplace_back("std::endl");
    std_keyWords.emplace_back("std::flush");
    std_keyWords.emplace_back("std::ends");
    std_keyWords.emplace_back("std::setw");
    std_keyWords.emplace_back("std::setfill");
    std_keyWords.emplace_back("std::setprecision");
    std_keyWords.emplace_back("std::setbase");
    std_keyWords.emplace_back("std::showbase");
    std_keyWords.emplace_back("std::noshowbase");
    std_keyWords.emplace_back("std::fixed");
    std_keyWords.emplace_back("std::scientific");
    std_keyWords.emplace_back("std::hex");
    std_keyWords.emplace_back("std::dec");
    std_keyWords.emplace_back("std::oct");
    std_keyWords.emplace_back("std::boolalpha");
    std_keyWords.emplace_back("std::noboolalpha");
    std_keyWords.emplace_back("std::left");
    std_keyWords.emplace_back("std::right");
    std_keyWords.emplace_back("std::internal");
    std_keyWords.emplace_back("std::quoted");

    // ==================== Input/output operations ====================
    std_keyWords.emplace_back("std::getline");
    std_keyWords.emplace_back("std::put");
    std_keyWords.emplace_back("std::get");
    std_keyWords.emplace_back("std::ws");
    std_keyWords.emplace_back("std::read");
    std_keyWords.emplace_back("std::write");
    std_keyWords.emplace_back("std::readsome");
    std_keyWords.emplace_back("std::gcount");
    std_keyWords.emplace_back("std::seekg");
    std_keyWords.emplace_back("std::seekp");
    std_keyWords.emplace_back("std::tellg");
    std_keyWords.emplace_back("std::tellp");
    std_keyWords.emplace_back("std::ios");
    std_keyWords.emplace_back("std::ios_base");
    // ==================== Basic mathematics ====================
    std_keyWords.emplace_back("std::abs");
    std_keyWords.emplace_back("std::fabs");
    std_keyWords.emplace_back("std::fmod");
    std_keyWords.emplace_back("std::remainder");
    std_keyWords.emplace_back("std::fma");
    std_keyWords.emplace_back("std::max");
    std_keyWords.emplace_back("std::min");
    std_keyWords.emplace_back("std::minmax");
    std_keyWords.emplace_back("std::clamp");

    // ==================== Powers and roots ====================
    std_keyWords.emplace_back("std::pow");
    std_keyWords.emplace_back("std::sqrt");
    std_keyWords.emplace_back("std::cbrt");
    std_keyWords.emplace_back("std::hypot");

    // ==================== Exponential and logarithmic functions ====================
    std_keyWords.emplace_back("std::exp");
    std_keyWords.emplace_back("std::exp2");
    std_keyWords.emplace_back("std::expm1");
    std_keyWords.emplace_back("std::log");
    std_keyWords.emplace_back("std::log10");
    std_keyWords.emplace_back("std::log2");
    std_keyWords.emplace_back("std::log1p");

    // ==================== Trigonometry ====================
    std_keyWords.emplace_back("std::sin");
    std_keyWords.emplace_back("std::cos");
    std_keyWords.emplace_back("std::tan");
    std_keyWords.emplace_back("std::asin");
    std_keyWords.emplace_back("std::acos");
    std_keyWords.emplace_back("std::atan");
    std_keyWords.emplace_back("std::atan2");
    std_keyWords.emplace_back("std::sinh");
    std_keyWords.emplace_back("std::cosh");
    std_keyWords.emplace_back("std::tanh");

    // ==================== Rounding ====================
    std_keyWords.emplace_back("std::ceil");
    std_keyWords.emplace_back("std::floor");
    std_keyWords.emplace_back("std::trunc");
    std_keyWords.emplace_back("std::round");
    std_keyWords.emplace_back("std::lround");
    std_keyWords.emplace_back("std::llround");
    std_keyWords.emplace_back("std::nearbyint");
    std_keyWords.emplace_back("std::rint");

    // ==================== Floating-point helpers ====================
    std_keyWords.emplace_back("std::isfinite");
    std_keyWords.emplace_back("std::isinf");
    std_keyWords.emplace_back("std::isnan");
    std_keyWords.emplace_back("std::signbit");
    std_keyWords.emplace_back("std::isnormal");
    std_keyWords.emplace_back("std::fpclassify");
    std_keyWords.emplace_back("std::nextafter");
    std_keyWords.emplace_back("std::copysign");

    // ==================== Numeric limits and constants ====================
    std_keyWords.emplace_back("std::numeric_limits");
    std_keyWords.emplace_back("std::int8_t");
    std_keyWords.emplace_back("std::int16_t");
    std_keyWords.emplace_back("std::int32_t");
    std_keyWords.emplace_back("std::int64_t");
    std_keyWords.emplace_back("std::uint8_t");
    std_keyWords.emplace_back("std::uint16_t");
    std_keyWords.emplace_back("std::uint32_t");
    std_keyWords.emplace_back("std::uint64_t");
    std_keyWords.emplace_back("std::size_t");
    std_keyWords.emplace_back("std::ptrdiff_t");
    std_keyWords.emplace_back("std::intptr_t");
    std_keyWords.emplace_back("std::uintptr_t");
    std_keyWords.emplace_back("std::byte");
    std_keyWords.emplace_back("std::bit_cast");
    std_keyWords.emplace_back("std::has_single_bit");
    std_keyWords.emplace_back("std::bit_width");
    std_keyWords.emplace_back("std::bit_floor");
    std_keyWords.emplace_back("std::bit_ceil");
    std_keyWords.emplace_back("std::popcount");
    std_keyWords.emplace_back("std::countl_zero");
    std_keyWords.emplace_back("std::countr_zero");
    std_keyWords.emplace_back("std::rotl");
    std_keyWords.emplace_back("std::rotr");
    // ==================== Chrono ====================
    std_keyWords.emplace_back("std::chrono");
    std_keyWords.emplace_back("std::chrono::duration");
    std_keyWords.emplace_back("std::chrono::time_point");
    std_keyWords.emplace_back("std::chrono::system_clock");
    std_keyWords.emplace_back("std::chrono::steady_clock");
    std_keyWords.emplace_back("std::chrono::high_resolution_clock");
    std_keyWords.emplace_back("std::chrono::duration_cast");
    std_keyWords.emplace_back("std::chrono::time_point_cast");
    std_keyWords.emplace_back("std::chrono::year");
    std_keyWords.emplace_back("std::chrono::month");
    std_keyWords.emplace_back("std::chrono::day");
    std_keyWords.emplace_back("std::chrono::year_month_day");
    std_keyWords.emplace_back("std::chrono::hh_mm_ss");

    // ==================== Duration literals ====================
    std_keyWords.emplace_back("std::chrono::nanoseconds");
    std_keyWords.emplace_back("std::chrono::microseconds");
    std_keyWords.emplace_back("std::chrono::milliseconds");
    std_keyWords.emplace_back("std::chrono::seconds");
    std_keyWords.emplace_back("std::chrono::minutes");
    std_keyWords.emplace_back("std::chrono::hours");

    // ==================== Random numbers ====================
    std_keyWords.emplace_back("std::random_device");
    std_keyWords.emplace_back("std::mt19937");
    std_keyWords.emplace_back("std::mt19937_64");
    std_keyWords.emplace_back("std::default_random_engine");
    std_keyWords.emplace_back("std::uniform_int_distribution");
    std_keyWords.emplace_back("std::uniform_real_distribution");
    std_keyWords.emplace_back("std::normal_distribution");
    std_keyWords.emplace_back("std::bernoulli_distribution");
    std_keyWords.emplace_back("std::poisson_distribution");
    std_keyWords.emplace_back("std::binomial_distribution");
    std_keyWords.emplace_back("std::generate_canonical");
    std_keyWords.emplace_back("std::seed_seq");
    // ==================== Filesystem ====================
    std_keyWords.emplace_back("std::filesystem");
    std_keyWords.emplace_back("std::filesystem::path");
    std_keyWords.emplace_back("std::filesystem::directory_entry");
    std_keyWords.emplace_back("std::filesystem::directory_iterator");
    std_keyWords.emplace_back("std::filesystem::recursive_directory_iterator");
    std_keyWords.emplace_back("std::filesystem::file_status");
    std_keyWords.emplace_back("std::filesystem::file_type");
    std_keyWords.emplace_back("std::filesystem::perms");

    // ==================== File and directory operations ====================
    std_keyWords.emplace_back("std::filesystem::exists");
    std_keyWords.emplace_back("std::filesystem::is_empty");
    std_keyWords.emplace_back("std::filesystem::is_directory");
    std_keyWords.emplace_back("std::filesystem::is_regular_file");
    std_keyWords.emplace_back("std::filesystem::is_symlink");
    std_keyWords.emplace_back("std::filesystem::create_directory");
    std_keyWords.emplace_back("std::filesystem::create_directories");
    std_keyWords.emplace_back("std::filesystem::remove");
    std_keyWords.emplace_back("std::filesystem::remove_all");
    std_keyWords.emplace_back("std::filesystem::rename");
    std_keyWords.emplace_back("std::filesystem::copy");
    std_keyWords.emplace_back("std::filesystem::copy_file");
    std_keyWords.emplace_back("std::filesystem::current_path");
    std_keyWords.emplace_back("std::filesystem::absolute");
    std_keyWords.emplace_back("std::filesystem::canonical");
    std_keyWords.emplace_back("std::filesystem::weakly_canonical");
    std_keyWords.emplace_back("std::filesystem::relative");
    std_keyWords.emplace_back("std::filesystem::proximate");
    std_keyWords.emplace_back("std::filesystem::file_size");
    std_keyWords.emplace_back("std::filesystem::last_write_time");
    std_keyWords.emplace_back("std::filesystem::permissions");
    std_keyWords.emplace_back("std::filesystem::space");
    std_keyWords.emplace_back("std::filesystem::temp_directory_path");
    std_keyWords.emplace_back("std::filesystem::read_symlink");
    std_keyWords.emplace_back("std::filesystem::create_symlink");
    std_keyWords.emplace_back("std::filesystem::create_hard_link");

    // ==================== Path operations ====================
    std_keyWords.emplace_back("std::filesystem::path::append");
    std_keyWords.emplace_back("std::filesystem::path::concat");
    std_keyWords.emplace_back("std::filesystem::path::clear");
    std_keyWords.emplace_back("std::filesystem::path::empty");
    std_keyWords.emplace_back("std::filesystem::path::filename");
    std_keyWords.emplace_back("std::filesystem::path::parent_path");
    std_keyWords.emplace_back("std::filesystem::path::extension");
    std_keyWords.emplace_back("std::filesystem::path::stem");
    std_keyWords.emplace_back("std::filesystem::path::root_name");
    std_keyWords.emplace_back("std::filesystem::path::root_directory");
    std_keyWords.emplace_back("std::filesystem::path::root_path");
    std_keyWords.emplace_back("std::filesystem::path::relative_path");
    std_keyWords.emplace_back("std::filesystem::path::replace_extension");
    std_keyWords.emplace_back("std::filesystem::path::has_filename");
    std_keyWords.emplace_back("std::filesystem::path::has_parent_path");
    // ==================== Threads ====================
    std_keyWords.emplace_back("std::thread");
    std_keyWords.emplace_back("std::jthread");
    std_keyWords.emplace_back("std::this_thread");
    std_keyWords.emplace_back("std::this_thread::get_id");
    std_keyWords.emplace_back("std::this_thread::sleep_for");
    std_keyWords.emplace_back("std::this_thread::sleep_until");
    std_keyWords.emplace_back("std::this_thread::yield");
    std_keyWords.emplace_back("std::thread::id");

    // ==================== Mutexes ====================
    std_keyWords.emplace_back("std::mutex");
    std_keyWords.emplace_back("std::recursive_mutex");
    std_keyWords.emplace_back("std::timed_mutex");
    std_keyWords.emplace_back("std::recursive_timed_mutex");
    std_keyWords.emplace_back("std::shared_mutex");
    std_keyWords.emplace_back("std::shared_timed_mutex");
    std_keyWords.emplace_back("std::lock_guard");
    std_keyWords.emplace_back("std::unique_lock");
    std_keyWords.emplace_back("std::shared_lock");
    std_keyWords.emplace_back("std::scoped_lock");

    // ==================== Condition variables ====================
    std_keyWords.emplace_back("std::condition_variable");
    std_keyWords.emplace_back("std::condition_variable_any");
    std_keyWords.emplace_back("std::notify_all_at_thread_exit");

    // ==================== Atomic operations ====================
    std_keyWords.emplace_back("std::atomic");
    std_keyWords.emplace_back("std::atomic_flag");
    std_keyWords.emplace_back("std::atomic_ref");
    std_keyWords.emplace_back("std::memory_order");
    std_keyWords.emplace_back("std::memory_order_relaxed");
    std_keyWords.emplace_back("std::memory_order_consume");
    std_keyWords.emplace_back("std::memory_order_acquire");
    std_keyWords.emplace_back("std::memory_order_release");
    std_keyWords.emplace_back("std::memory_order_acq_rel");
    std_keyWords.emplace_back("std::memory_order_seq_cst");
    std_keyWords.emplace_back("std::atomic_thread_fence");
    std_keyWords.emplace_back("std::atomic_signal_fence");

    // ==================== Futures and tasks ====================
    std_keyWords.emplace_back("std::future");
    std_keyWords.emplace_back("std::shared_future");
    std_keyWords.emplace_back("std::promise");
    std_keyWords.emplace_back("std::packaged_task");
    std_keyWords.emplace_back("std::async");
    std_keyWords.emplace_back("std::launch");
    std_keyWords.emplace_back("std::future_status");
    std_keyWords.emplace_back("std::future_error");
    std_keyWords.emplace_back("std::stop_token");
    std_keyWords.emplace_back("std::stop_source");
    std_keyWords.emplace_back("std::stop_callback");
    std_keyWords.emplace_back("std::latch");
    std_keyWords.emplace_back("std::barrier");
    std_keyWords.emplace_back("std::counting_semaphore");
    std_keyWords.emplace_back("std::binary_semaphore");

    // ==================== Synchronization utilities ====================
    std_keyWords.emplace_back("std::call_once");
    std_keyWords.emplace_back("std::once_flag");
    std_keyWords.emplace_back("std::atomic_wait");
    std_keyWords.emplace_back("std::atomic_notify_one");
    std_keyWords.emplace_back("std::atomic_notify_all");
    // ==================== Standard exceptions ====================
    std_keyWords.emplace_back("std::exception");
    std_keyWords.emplace_back("std::runtime_error");
    std_keyWords.emplace_back("std::logic_error");
    std_keyWords.emplace_back("std::invalid_argument");
    std_keyWords.emplace_back("std::domain_error");
    std_keyWords.emplace_back("std::length_error");
    std_keyWords.emplace_back("std::out_of_range");
    std_keyWords.emplace_back("std::range_error");
    std_keyWords.emplace_back("std::overflow_error");
    std_keyWords.emplace_back("std::underflow_error");
    std_keyWords.emplace_back("std::bad_alloc");
    std_keyWords.emplace_back("std::bad_array_new_length");
    std_keyWords.emplace_back("std::bad_cast");
    std_keyWords.emplace_back("std::bad_typeid");
    std_keyWords.emplace_back("std::bad_exception");
    std_keyWords.emplace_back("std::bad_function_call");
    std_keyWords.emplace_back("std::bad_optional_access");
    std_keyWords.emplace_back("std::bad_variant_access");
    std_keyWords.emplace_back("std::bad_any_cast");
    std_keyWords.emplace_back("std::system_error");
    std_keyWords.emplace_back("std::filesystem::filesystem_error");

    // ==================== Error handling utilities ====================
    std_keyWords.emplace_back("std::error_code");
    std_keyWords.emplace_back("std::error_condition");
    std_keyWords.emplace_back("std::error_category");
    std_keyWords.emplace_back("std::generic_category");
    std_keyWords.emplace_back("std::system_category");
    std_keyWords.emplace_back("std::current_exception");
    std_keyWords.emplace_back("std::rethrow_exception");
    std_keyWords.emplace_back("std::make_exception_ptr");
    std_keyWords.emplace_back("std::exception_ptr");
    std_keyWords.emplace_back("std::nested_exception");
    std_keyWords.emplace_back("std::throw_with_nested");
    std_keyWords.emplace_back("std::rethrow_if_nested");

    // ==================== Assertions and debugging ====================
    std_keyWords.emplace_back("assert");
    std_keyWords.emplace_back("static_assert");
    std_keyWords.emplace_back("std::source_location");
    std_keyWords.emplace_back("std::stacktrace");
    std_keyWords.emplace_back("std::stacktrace_entry");
    std_keyWords.emplace_back("std::abort");
    std_keyWords.emplace_back("std::terminate");
    std_keyWords.emplace_back("std::set_terminate");
    std_keyWords.emplace_back("std::quick_exit");
    std_keyWords.emplace_back("std::exit");
    std_keyWords.emplace_back("std::atexit");
    std_keyWords.emplace_back("std::errno");
    // ==================== Type traits ====================
    std_keyWords.emplace_back("std::is_same");
    std_keyWords.emplace_back("std::is_same_v");
    std_keyWords.emplace_back("std::is_integral");
    std_keyWords.emplace_back("std::is_integral_v");
    std_keyWords.emplace_back("std::is_floating_point");
    std_keyWords.emplace_back("std::is_floating_point_v");
    std_keyWords.emplace_back("std::is_arithmetic");
    std_keyWords.emplace_back("std::is_arithmetic_v");
    std_keyWords.emplace_back("std::is_pointer");
    std_keyWords.emplace_back("std::is_pointer_v");
    std_keyWords.emplace_back("std::is_reference");
    std_keyWords.emplace_back("std::is_reference_v");
    std_keyWords.emplace_back("std::is_const");
    std_keyWords.emplace_back("std::is_const_v");
    std_keyWords.emplace_back("std::is_volatile");
    std_keyWords.emplace_back("std::is_volatile_v");
    std_keyWords.emplace_back("std::is_array");
    std_keyWords.emplace_back("std::is_array_v");
    std_keyWords.emplace_back("std::is_enum");
    std_keyWords.emplace_back("std::is_enum_v");
    std_keyWords.emplace_back("std::is_class");
    std_keyWords.emplace_back("std::is_class_v");
    std_keyWords.emplace_back("std::is_base_of");
    std_keyWords.emplace_back("std::is_base_of_v");
    std_keyWords.emplace_back("std::is_convertible");
    std_keyWords.emplace_back("std::is_convertible_v");
    std_keyWords.emplace_back("std::is_constructible");
    std_keyWords.emplace_back("std::is_constructible_v");
    std_keyWords.emplace_back("std::is_default_constructible");
    std_keyWords.emplace_back("std::is_default_constructible_v");
    std_keyWords.emplace_back("std::is_copy_constructible");
    std_keyWords.emplace_back("std::is_copy_constructible_v");
    std_keyWords.emplace_back("std::is_move_constructible");
    std_keyWords.emplace_back("std::is_move_constructible_v");
    std_keyWords.emplace_back("std::is_trivially_copyable");
    std_keyWords.emplace_back("std::is_trivially_copyable_v");
    std_keyWords.emplace_back("std::is_standard_layout");
    std_keyWords.emplace_back("std::is_standard_layout_v");

    // ==================== Type transformations ====================
    std_keyWords.emplace_back("std::remove_const");
    std_keyWords.emplace_back("std::remove_const_t");
    std_keyWords.emplace_back("std::remove_volatile");
    std_keyWords.emplace_back("std::remove_volatile_t");
    std_keyWords.emplace_back("std::remove_cv");
    std_keyWords.emplace_back("std::remove_cv_t");
    std_keyWords.emplace_back("std::remove_reference");
    std_keyWords.emplace_back("std::remove_reference_t");
    std_keyWords.emplace_back("std::remove_pointer");
    std_keyWords.emplace_back("std::remove_pointer_t");
    std_keyWords.emplace_back("std::decay");
    std_keyWords.emplace_back("std::decay_t");
    std_keyWords.emplace_back("std::enable_if");
    std_keyWords.emplace_back("std::enable_if_t");
    std_keyWords.emplace_back("std::conditional");
    std_keyWords.emplace_back("std::conditional_t");
    std_keyWords.emplace_back("std::common_type");
    std_keyWords.emplace_back("std::common_type_t");
    std_keyWords.emplace_back("std::common_reference");
    std_keyWords.emplace_back("std::common_reference_t");
    std_keyWords.emplace_back("std::underlying_type");
    std_keyWords.emplace_back("std::underlying_type_t");
    std_keyWords.emplace_back("std::invoke_result");
    std_keyWords.emplace_back("std::invoke_result_t");
    std_keyWords.emplace_back("std::result_of");
    std_keyWords.emplace_back("std::result_of_t");
    std_keyWords.emplace_back("std::void_t");
    std_keyWords.emplace_back("std::type_identity");
    std_keyWords.emplace_back("std::type_identity_t");

    // ==================== Concepts ====================
    std_keyWords.emplace_back("std::same_as");
    std_keyWords.emplace_back("std::derived_from");
    std_keyWords.emplace_back("std::convertible_to");
    std_keyWords.emplace_back("std::common_reference_with");
    std_keyWords.emplace_back("std::common_with");
    std_keyWords.emplace_back("std::integral");
    std_keyWords.emplace_back("std::signed_integral");
    std_keyWords.emplace_back("std::unsigned_integral");
    std_keyWords.emplace_back("std::floating_point");
    std_keyWords.emplace_back("std::assignable_from");
    std_keyWords.emplace_back("std::default_initializable");
    std_keyWords.emplace_back("std::move_constructible");
    std_keyWords.emplace_back("std::copy_constructible");
    std_keyWords.emplace_back("std::swappable");
    std_keyWords.emplace_back("std::destructible");
    std_keyWords.emplace_back("std::constructible_from");
    std_keyWords.emplace_back("std::invocable");
    std_keyWords.emplace_back("std::regular_invocable");
    std_keyWords.emplace_back("std::predicate");
    std_keyWords.emplace_back("std::relation");
    std_keyWords.emplace_back("std::strict_weak_order");
    std_keyWords.emplace_back("std::equality_comparable");
    std_keyWords.emplace_back("std::totally_ordered");
    std_keyWords.emplace_back("std::ranges::range");
    std_keyWords.emplace_back("std::ranges::input_range");
    std_keyWords.emplace_back("std::ranges::forward_range");
    std_keyWords.emplace_back("std::ranges::bidirectional_range");
    std_keyWords.emplace_back("std::ranges::random_access_range");
    std_keyWords.emplace_back("std::ranges::contiguous_range");
    std_keyWords.emplace_back("std::ranges::sized_range");
    // ==================== Iterator utilities ====================
    std_keyWords.emplace_back("std::begin");
    std_keyWords.emplace_back("std::end");
    std_keyWords.emplace_back("std::cbegin");
    std_keyWords.emplace_back("std::cend");
    std_keyWords.emplace_back("std::rbegin");
    std_keyWords.emplace_back("std::rend");
    std_keyWords.emplace_back("std::crbegin");
    std_keyWords.emplace_back("std::crend");
    std_keyWords.emplace_back("std::size");
    std_keyWords.emplace_back("std::ssize");
    std_keyWords.emplace_back("std::empty");
    std_keyWords.emplace_back("std::data");
    std_keyWords.emplace_back("std::distance");
    std_keyWords.emplace_back("std::advance");
    std_keyWords.emplace_back("std::next");
    std_keyWords.emplace_back("std::prev");
    std_keyWords.emplace_back("std::iter_move");
    std_keyWords.emplace_back("std::iter_swap");
    std_keyWords.emplace_back("std::reverse_iterator");
    std_keyWords.emplace_back("std::move_iterator");
    std_keyWords.emplace_back("std::counted_iterator");
    std_keyWords.emplace_back("std::common_iterator");
    std_keyWords.emplace_back("std::istream_iterator");
    std_keyWords.emplace_back("std::ostream_iterator");
    std_keyWords.emplace_back("std::back_insert_iterator");
    std_keyWords.emplace_back("std::front_insert_iterator");
    std_keyWords.emplace_back("std::insert_iterator");
    std_keyWords.emplace_back("std::back_inserter");
    std_keyWords.emplace_back("std::front_inserter");
    std_keyWords.emplace_back("std::inserter");

    // ==================== Bit operations ====================
    std_keyWords.emplace_back("std::bitset");
    std_keyWords.emplace_back("std::bit_cast");
    std_keyWords.emplace_back("std::bit_width");
    std_keyWords.emplace_back("std::bit_floor");
    std_keyWords.emplace_back("std::bit_ceil");
    std_keyWords.emplace_back("std::has_single_bit");
    std_keyWords.emplace_back("std::popcount");
    std_keyWords.emplace_back("std::countl_zero");
    std_keyWords.emplace_back("std::countl_one");
    std_keyWords.emplace_back("std::countr_zero");
    std_keyWords.emplace_back("std::countr_one");
    std_keyWords.emplace_back("std::rotl");
    std_keyWords.emplace_back("std::rotr");

    // ==================== Type information ====================
    std_keyWords.emplace_back("std::type_info");
    std_keyWords.emplace_back("std::type_index");
    std_keyWords.emplace_back("std::typeid");
    std_keyWords.emplace_back("std::bad_cast");
    std_keyWords.emplace_back("std::bad_typeid");

    // ==================== Coroutines ====================
    std_keyWords.emplace_back("std::coroutine_handle");
    std_keyWords.emplace_back("std::coroutine_traits");
    std_keyWords.emplace_back("std::suspend_never");
    std_keyWords.emplace_back("std::suspend_always");
    std_keyWords.emplace_back("std::noop_coroutine");
    std_keyWords.emplace_back("std::generator");

    // ==================== Execution and parallel algorithms ====================
    std_keyWords.emplace_back("std::execution");
    std_keyWords.emplace_back("std::execution::seq");
    std_keyWords.emplace_back("std::execution::par");
    std_keyWords.emplace_back("std::execution::par_unseq");
    std_keyWords.emplace_back("std::execution::unseq");

    // ==================== C++23 / C++26 additions ====================
    std_keyWords.emplace_back("std::expected");
    std_keyWords.emplace_back("std::unexpected");
    std_keyWords.emplace_back("std::unreachable");
    std_keyWords.emplace_back("std::println");
    std_keyWords.emplace_back("std::print");
    std_keyWords.emplace_back("std::stacktrace");
    std_keyWords.emplace_back("std::stacktrace_entry");
    std_keyWords.emplace_back("std::generator");
    std_keyWords.emplace_back("std::inplace_vector");
    std_keyWords.emplace_back("std::hive");
    std_keyWords.emplace_back("std::text_encoding");
    std_keyWords.emplace_back("std::simd");
    std_keyWords.emplace_back("std::linalg");

    // ==================== Namespaces ====================
    LDDrift_keyWords.emplace_back("LDDrift");
    LDDrift_keyWords.emplace_back("LDDrift::Actors");
    LDDrift_keyWords.emplace_back("LDDrift::ActorType");
    LDDrift_keyWords.emplace_back("LDDrift::Assertions");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI");
    LDDrift_keyWords.emplace_back("LDDrift::Event");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse");
    LDDrift_keyWords.emplace_back("LDDrift::func");
    LDDrift_keyWords.emplace_back("LDDrift::input");
    LDDrift_keyWords.emplace_back("LDDrift::Anonymous");

    // ==================== Core types and aliases ====================
    LDDrift_keyWords.emplace_back("LDDrift::Angle");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol");
    LDDrift_keyWords.emplace_back("LDDrift::ShapeData");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Polygon");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::PNT");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Dir");
    LDDrift_keyWords.emplace_back("LDDrift::ActorType::convex");
    LDDrift_keyWords.emplace_back("LDDrift::ActorType::concave");
    LDDrift_keyWords.emplace_back("LDDrift::Triangulation");
    LDDrift_keyWords.emplace_back("LDDrift::Triangulation<LDDrift::ActorType::convex>");
    LDDrift_keyWords.emplace_back("LDDrift::Triangulation<LDDrift::ActorType::concave>");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer");
    LDDrift_keyWords.emplace_back("LDDrift::Window");
    LDDrift_keyWords.emplace_back("LDDrift::Core");
    LDDrift_keyWords.emplace_back("LDDrift::Scene");
    LDDrift_keyWords.emplace_back("LDDrift::GUI");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::EditorWindowsData");
    LDDrift_keyWords.emplace_back("LDDrift::Compile");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::CompileError");
    LDDrift_keyWords.emplace_back("LDDrift::CompileBuildStatus");
    LDDrift_keyWords.emplace_back("LDDrift::CodePathfinder");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::Extract");
    LDDrift_keyWords.emplace_back("LDDrift::GuiLogic");
    LDDrift_keyWords.emplace_back("LDDrift::PointHitTesting");
    LDDrift_keyWords.emplace_back("LDDrift::Transform");
    LDDrift_keyWords.emplace_back("LDDrift::SettingUserProject");
    LDDrift_keyWords.emplace_back("LDDrift::WR_SettingSystem");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::LinuxMouseKeyCode");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::WindowsMouseKeyCode");
    LDDrift_keyWords.emplace_back("LDDrift::DeviceRole");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::BeginPlayFunction");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::TickFunction");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::EndPlayFunction");
    LDDrift_keyWords.emplace_back("LDDrift::ShapeData::Vertex");

    // ==================== Assertion API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Assertions::PrintLog");
    LDDrift_keyWords.emplace_back("GLB_assert");
    LDDrift_keyWords.emplace_back("COF_assert");
    LDDrift_keyWords.emplace_back("NAO_assert");
    LDDrift_keyWords.emplace_back("OOR_assert");
    LDDrift_keyWords.emplace_back("CTM_assert");
    LDDrift_keyWords.emplace_back("NPV_assert");
    LDDrift_keyWords.emplace_back("GREEN");
    LDDrift_keyWords.emplace_back("YELLOW");
    LDDrift_keyWords.emplace_back("RED");
    LDDrift_keyWords.emplace_back("RESET");

    // ==================== EngineAPI API ====================
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::project_watch_tower");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::beginPlay");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::tick");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::endPlay");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::handle");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::hModule");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::AfterCompileProject");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::SetProjectWatchTowerPTR");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::BeginPlay");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::Tick");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::EndPlay");
    LDDrift_keyWords.emplace_back("LDDrift::EngineAPI::DestroyEngineAPI");

    // ==================== General functions ====================
    LDDrift_keyWords.emplace_back("LDDrift::func::GetHostName");
    LDDrift_keyWords.emplace_back("LDDrift::func::GetExecutablePath");
    LDDrift_keyWords.emplace_back("LDDrift::func::GetDefaultDiskPath");
    LDDrift_keyWords.emplace_back("LDDrift::func::InitDeltaTime");
    LDDrift_keyWords.emplace_back("LDDrift::func::GetDeltaTime");
    LDDrift_keyWords.emplace_back("LDDrift::func::GetSceneObjectPointer");
    LDDrift_keyWords.emplace_back("lastTime");
    LDDrift_keyWords.emplace_back("currentTime");
    LDDrift_keyWords.emplace_back("deltaTime");
    LDDrift_keyWords.emplace_back("LD_uint");
    LDDrift_keyWords.emplace_back("LD_lint");
    LDDrift_keyWords.emplace_back("LD_ulint");
    LDDrift_keyWords.emplace_back("IsKeyPressedInFrame");
    LDDrift_keyWords.emplace_back("IsKeyPressedInFrame::Before");
    LDDrift_keyWords.emplace_back("IsKeyPressedInFrame::Current");
    LDDrift_keyWords.emplace_back("ToUpdateValues");
    LDDrift_keyWords.emplace_back("WindowsKeyCodes");
    LDDrift_keyWords.emplace_back("TargetKeys");

    // ==================== Angle API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Angle::angle");
    LDDrift_keyWords.emplace_back("LDDrift::Angle::GetAngleRadians");

    // ==================== VecPos2D API ====================
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::X");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::Y");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::Normalize");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::NormalLine");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator-");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator+");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator*");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator/");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator-=");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator+=");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator*=");
    LDDrift_keyWords.emplace_back("LDDrift::VecPos2D::operator/=");

    // ==================== VecCol API ====================
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::R");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::G");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::B");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::A");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::Red");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::Green");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::Blue");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::Yellow");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::Orange");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::Purple");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::White");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::Black");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::SetColor");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator+=");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator-=");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator*=");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator/=");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator+");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator-");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator*");
    LDDrift_keyWords.emplace_back("LDDrift::VecCol::operator/");

    // ==================== Shape API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetGlobalPoints");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetNDC_Points");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetPointCount");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetPointCount");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetPoint");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetGlobalPoint");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetNDC_Point");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetSpeed");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetSpeedNDC_X");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetSpeedNDC_Y");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::Move");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::Rotate");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetSpeed");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetOriginalPosition");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetOriginalPositionToCenter");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetOriginalPosition");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetOriginalPositionToCenter");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetPointColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetPointColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetColorOfPoints");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::ResetPointCount");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::ResetPoints");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::ResetColorOfPoints");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::ResetOriginalPosition");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetFillColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetThickness");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetScreenSize");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::SetAllPointsColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::IsFillShape");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::IsHaveThickness");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::GetThickness");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::TransformPoints");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::CalculateAverageVertexColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::CalculateAveragePointPosition");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::Rebuild");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Shape::ShapeIsConvex");

    // ==================== Circle API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::SetRadius");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::SetCirclePosition");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::GetCirclePosition");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::GetRadius");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::CalculateAverageVertexColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::Rebuild");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::Rotate");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Circle::Move");

    // ==================== Polygon API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Polygon::CalculateAverageVertexColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Polygon::Rebuild");

    // ==================== Line API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::PNT::Point_1");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::PNT::Point_2");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::PNT::Point_3");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::CreateTriangles");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::SetFirstPoint");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::SetSecondPoint");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::GetThickness");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::GetFirstPoint");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::GetSecondPoint");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::GetPoints");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::GetColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::SetLineColor");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::SetThickness");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Line::SetScreenSize");

    // ==================== ShapeData API ====================
    LDDrift_keyWords.emplace_back("LDDrift::ShapeData::Vertices");
    LDDrift_keyWords.emplace_back("LDDrift::ShapeData::PointsColors");

    // ==================== Core API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Core::consoleBuffer");
    LDDrift_keyWords.emplace_back("LDDrift::Core::oldC_outBuf");
    LDDrift_keyWords.emplace_back("LDDrift::Core::engineRun");
    LDDrift_keyWords.emplace_back("LDDrift::Core::window");
    LDDrift_keyWords.emplace_back("LDDrift::Core::render");
    LDDrift_keyWords.emplace_back("LDDrift::Core::projectWatchTower");
    LDDrift_keyWords.emplace_back("LDDrift::Core::pointHitTesting");
    LDDrift_keyWords.emplace_back("LDDrift::Core::gui");
    LDDrift_keyWords.emplace_back("LDDrift::Core::compile");
    LDDrift_keyWords.emplace_back("LDDrift::Core::scene");
    LDDrift_keyWords.emplace_back("LDDrift::Core::codePathfinder");
    LDDrift_keyWords.emplace_back("LDDrift::Core::Begin");
    LDDrift_keyWords.emplace_back("LDDrift::Core::EngineHandler");

    // ==================== Scene API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Scene::SetCorePTR");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::SetRendererPTR");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::SendShapesToRender");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::FindCircleWithName");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::GetCircle");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::CreateCircleShape");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::FindPolygonWithName");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::GetPolygon");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::CreatePolygonShape");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::FindLineWithName");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::GetLine");
    LDDrift_keyWords.emplace_back("LDDrift::Scene::CreateLineActor");

    // ==================== Renderer API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::Initialize");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::RebuildShapes");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::SetWidthScreen");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::SetHeightScreen");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::GetProgram");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::SendDataToGPU");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::AddShapeToRender");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::AddLineToRender");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::UpdateShapeData");
    LDDrift_keyWords.emplace_back("LDDrift::Renderer::render");

    // ==================== Window API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Window::SetRendererPTR");
    LDDrift_keyWords.emplace_back("LDDrift::Window::CreateWindow");
    LDDrift_keyWords.emplace_back("LDDrift::Window::CreateFullscreenWindow");
    LDDrift_keyWords.emplace_back("LDDrift::Window::DestroyWindow");
    LDDrift_keyWords.emplace_back("LDDrift::Window::SetFillScreenColor");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetFillScreenColor");
    LDDrift_keyWords.emplace_back("LDDrift::Window::LockWindow");
    LDDrift_keyWords.emplace_back("LDDrift::Window::ClearBuffer");
    LDDrift_keyWords.emplace_back("LDDrift::Window::SetTitle");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetTitle");
    LDDrift_keyWords.emplace_back("LDDrift::Window::SetSize");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetWindowSize");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetViewportSize");
    LDDrift_keyWords.emplace_back("LDDrift::Window::SetPosition");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetPosition");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetCenterPosition");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetWidth");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetHeight");
    LDDrift_keyWords.emplace_back("LDDrift::Window::GetWindow");
    LDDrift_keyWords.emplace_back("LDDrift::Window::FrameBufferSizeCallback");
    LDDrift_keyWords.emplace_back("LDDrift::Window::Update");
    LDDrift_keyWords.emplace_back("LDDrift::Window::ScreenIsOpen");

    // ==================== Transform API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Transform::widthScreen");
    LDDrift_keyWords.emplace_back("LDDrift::Transform::heightScreen");
    LDDrift_keyWords.emplace_back("LDDrift::Transform::halfWidthScreen");
    LDDrift_keyWords.emplace_back("LDDrift::Transform::halfHeightScreen");
    LDDrift_keyWords.emplace_back("LDDrift::Transform::TransformToNDC_Position");
    LDDrift_keyWords.emplace_back("LDDrift::Transform::TransformToGlobalPosition");

    // ==================== Point hit testing API ====================
    LDDrift_keyWords.emplace_back("LDDrift::PointHitTesting::pointHitTesting");

    // ==================== Triangulation API ====================
    LDDrift_keyWords.emplace_back("LDDrift::Triangulation<LDDrift::ActorType::convex>::SetShapeTarget");
    LDDrift_keyWords.emplace_back("LDDrift::Triangulation<LDDrift::ActorType::convex>::CreateTriangles");
    LDDrift_keyWords.emplace_back("LDDrift::Triangulation<LDDrift::ActorType::concave>::SetShapeTarget");
    LDDrift_keyWords.emplace_back("LDDrift::Triangulation<LDDrift::ActorType::concave>::CreateTriangles");

    // ==================== ProjectWatchTower API ====================
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::Extract::GetLastFileName");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::Extract::GetBodyWithoutLastFileName");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::Extract::ExtractPaths");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::isFilePath");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::SetPaths");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::PathIsFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::GetPaths");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::IsAvailableFileInProject");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::CreateBuildFolder");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::CreateCmakeListsTxtFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::CreateCompileLogFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::FindFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::isCmakeFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::CreateNewProject");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::SetProjectPath");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::WriteCodeToFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::CreateNewFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::RemoveBuildFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::RemoveFile");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::GetBuildFolderPath");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::GetProjectPath");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::GetProjectDetails");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::GetCompileLogPath");
    LDDrift_keyWords.emplace_back("LDDrift::ProjectWatchTower::GetProjectName");

    // ==================== Compilation API ====================
    LDDrift_keyWords.emplace_back("LDDrift::CompileBuildStatus::Idle");
    LDDrift_keyWords.emplace_back("LDDrift::CompileBuildStatus::Building");
    LDDrift_keyWords.emplace_back("LDDrift::CompileBuildStatus::Succeeded");
    LDDrift_keyWords.emplace_back("LDDrift::CompileBuildStatus::Failed");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::CompileError::file");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::CompileError::line");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::CompileError::column");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::CompileError::severity");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::CompileError::message");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::init");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::BuildProject");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::GetErrorLog");
    LDDrift_keyWords.emplace_back("LDDrift::Compile::GetStatus");

    // ==================== CodePathfinder API ====================
    LDDrift_keyWords.emplace_back("LDDrift::CodePathfinder::initializeCodePathfinder");
    LDDrift_keyWords.emplace_back("LDDrift::CodePathfinder::GetCodeSuggestions");

    // ==================== GUI API ====================
    LDDrift_keyWords.emplace_back("LDDrift::GUI::ExtractTextFromString");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::name");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::canMoveWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::canResizeWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::textPrintInWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::position");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::size");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::Show");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::DefaultWindowsData::searchBuffer");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::EditorWindowsData::buffer");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::EditorWindowsData::name");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::EditorWindowsData::editorWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::EditorWindowsData::Show");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::ImGuiEditorWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::defaultWindows");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::ProjectWatchTower_PTR");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::CompilePTR");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::runGame");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::UpdateWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::Initialize");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::SetProjectWatchTower_PTR");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::SetCompilePTR");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::CreateNewWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::CreateNewEditor");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::GetCodeBuffer");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::SetTextForWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::RenameEditorWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::SetCorePTR");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::SetShowEditorWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::GetWindow");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::GetWindowPTR");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::BeginRenderGUI");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::EndRenderGUI");
    LDDrift_keyWords.emplace_back("LDDrift::GUI::CodeEditorCallback");

    // ==================== GuiLogic API ====================
    LDDrift_keyWords.emplace_back("LDDrift::GuiLogic::SetProjectWatchTowerPtr");
    LDDrift_keyWords.emplace_back("LDDrift::GuiLogic::PressEnterInSearchBarInProjectWatchTower");
    LDDrift_keyWords.emplace_back("LDDrift::GuiLogic::ProjectManagerHandling");
    LDDrift_keyWords.emplace_back("LDDrift::Anonymous::projectWatchTowerPTR");

    // ==================== Settings API ====================
    LDDrift_keyWords.emplace_back("LDDrift::WR_SettingSystem::SetProjectWatchTowerPTR");
    LDDrift_keyWords.emplace_back("LDDrift::WR_SettingSystem::Init");
    LDDrift_keyWords.emplace_back("LDDrift::WR_SettingSystem::CreateSettingFolder");
    LDDrift_keyWords.emplace_back("LDDrift::WR_SettingSystem::WriteSettingsOfUserProject");
    LDDrift_keyWords.emplace_back("LDDrift::WR_SettingSystem::ReadSettingsOfUserProject");

    // ==================== Keyboard and mouse API ====================
    LDDrift_keyWords.emplace_back("LDDrift::GetFileKeyboardInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::OpenFileKeyboardInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::CloseFileKeyboardInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::GetFileMouseInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::OpenFileMouseInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::CloseFileMouseInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::GetDeviceRole");
    LDDrift_keyWords.emplace_back("LDDrift::TargetKeys");
    LDDrift_keyWords.emplace_back("LDDrift::LinuxKeyboard");
    LDDrift_keyWords.emplace_back("LDDrift::LinuxMouse");
    LDDrift_keyWords.emplace_back("LDDrift::KeyBoardKeyName");
    LDDrift_keyWords.emplace_back("LDDrift::KeyStringName");
    LDDrift_keyWords.emplace_back("LDDrift::fileKeyboardInputEvent_V");
    LDDrift_keyWords.emplace_back("LDDrift::fileMouseInputEvent_V");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::Init");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::SetKeyTarget");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::GetKeyInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::IsKeyPressed");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::IsKeyHeld");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::IsKeyReleased");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::GetKeyPressed");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::GetKeyHeld");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::GetKeyReleased");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::Update");
    LDDrift_keyWords.emplace_back("LDDrift::input::Keyboard::Destroy");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::Init");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::GetMouseInputEvent");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::GetCursorPos");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsLeftMouseButtonPressed");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsRightMouseButtonPressed");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsMiddleMouseButtonPressed");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsXButton1Pressed");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsXButton2Pressed");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsLeftMouseButtonReleased");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsRightMouseButtonReleased");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsMiddleMouseButtonReleased");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsXButton1Released");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsXButton2Released");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsLeftMouseButtonHeld");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsRightMouseButtonHeld");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsMiddleMouseButtonHeld");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsXButton1Held");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::IsXButton2Held");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::Update");
    LDDrift_keyWords.emplace_back("LDDrift::input::Mouse::Destroy");

    // ==================== Shape direction enumerators ====================
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Dir::UP");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Dir::DOWN");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Dir::LEFT");
    LDDrift_keyWords.emplace_back("LDDrift::Actors::Dir::RIGHT");

    // ==================== Input device role enumerators ====================
    LDDrift_keyWords.emplace_back("LDDrift::DeviceRole::Keyboard");
    LDDrift_keyWords.emplace_back("LDDrift::DeviceRole::Mouse");
    LDDrift_keyWords.emplace_back("LDDrift::DeviceRole::Unknown");

    // ==================== Linux keyboard key enumerators ====================
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RESERVED");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ESC");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_1");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_2");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_3");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_4");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_5");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_6");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_7");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_8");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_9");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_0");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MINUS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_EQUALS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_BACKSPACE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_TAB");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_Q");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_W");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_E");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_R");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_T");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_Y");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_U");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_I");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_O");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_P");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LBRACKET");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RBRACKET");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ENTER");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LCONTROL");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_A");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_S");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_D");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_G");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_H");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_J");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_K");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_L");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SEMICOLON");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_APOSTROPHE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_GRAVE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LSHIFT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_BACKSLASH");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_Z");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_X");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_C");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_V");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_B");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_N");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_M");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_COMMA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_DOT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SLASH");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RSHIFT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPASTERISK");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LALT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SPACE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_CAPSLOCK");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F1");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F2");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F3");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F4");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F5");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F6");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F7");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F8");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F9");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F10");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_NUMLOCK");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SCROLLLOCK");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP7");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP8");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP9");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPMINUS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP4");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP5");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP6");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPPLUS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP1");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP2");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP3");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KP0");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPDOT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RESERVED_84");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ZENKAKUHANKAKU");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_102ND");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F11");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_F12");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RO");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KATAKANA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_HIRAGANA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_HENKAN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KATAKANAHIRAGANA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MUHENKAN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPJPCOMMA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPENTER");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RCONTROL");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPSLASH");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SYSRQ");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RALT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LINEFEED");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_HOME");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_UP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PAGEUP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LEFT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RIGHT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_END");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_DOWN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PAGEDOWN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_INSERT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_DELETE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MACRO");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MUTE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_VOLUMEDOWN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_VOLUMEUP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_POWER");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPEQUAL");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPPLUSMINUS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PAUSE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SCALE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPCOMMA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_HANGEUL");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_HANJA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_YEN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_LMETA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RMETA");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_COMPOSE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_STOP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_AGAIN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PROPS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_UNDO");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_FRONT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_COPY");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_OPEN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PASTE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_FIND");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_CUT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_HELP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MENU");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_CALC");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SETUP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SLEEP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_WAKEUP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_FILE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SENDFILE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_DELETEFILE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_XFER");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PROG1");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PROG2");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_WWW");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MSDOS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_COFFEE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ROTATE_DISPLAY");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_CYCLEWINDOWS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MAIL");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_BOOKMARKS");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_COMPUTER");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_BACK");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_FORWARD");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_CLOSECD");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_EJECTCD");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_EJECTCLOSECD");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_NEXTSONG");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PLAYPAUSE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PREVIOUSSONG");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_STOPCD");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_RECORD");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_REWIND");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_PHONE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_ISO");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_CONFIG");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_HOMEPAGE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_REFRESH");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_EXIT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_MOVE");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_EDIT");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SCROLLUP");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_SCROLLDOWN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPLEFTPAREN");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Keyboard::LinuxKeyboardKeyCode::Key_KPRIGHTPAREN");

    // ==================== Linux mouse button enumerators ====================
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::LinuxMouseKeyCode::LeftButton");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::LinuxMouseKeyCode::RightButton");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::LinuxMouseKeyCode::MiddleButton");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::LinuxMouseKeyCode::XButton1");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::LinuxMouseKeyCode::XButton2");

    // ==================== Windows mouse button enumerators ====================
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::WindowsMouseKeyCode::LeftButton");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::WindowsMouseKeyCode::RightButton");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::WindowsMouseKeyCode::MiddleButton");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::WindowsMouseKeyCode::XButton1");
    LDDrift_keyWords.emplace_back("LDDrift::Event::Mouse::WindowsMouseKeyCode::XButton2");

    // ==================== Project macros and constants ====================
    LDDrift_keyWords.emplace_back("NOT_AVAILABLE_OS");
    LDDrift_keyWords.emplace_back("NO_EVENT_IS_AVAILABLE_TO_READ");
    LDDrift_keyWords.emplace_back("FULLSCREEN_WINDOW_WIDTH");
    LDDrift_keyWords.emplace_back("FULLSCREEN_WINDOW_HEIGHT");
    LDDrift_keyWords.emplace_back("HALF_FULLSCREEN_WINDOW_WIDTH");
    LDDrift_keyWords.emplace_back("HALF_FULLSCREEN_WINDOW_HEIGHT");
    LDDrift_keyWords.emplace_back("VIEWPORT_WINDOW_WIDTH");
    LDDrift_keyWords.emplace_back("VIEWPORT_WINDOW_HEIGHT");
    LDDrift_keyWords.emplace_back("HALF_VIEWPORT_WINDOW_WIDTH");
    LDDrift_keyWords.emplace_back("HALF_VIEWPORT_WINDOW_HEIGHT");
    LDDrift_keyWords.emplace_back("PROJECT_WATCH_TOWER_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("PROJECT_WATCH_TOWER_X_SIZE");
    LDDrift_keyWords.emplace_back("PROJECT_WATCH_TOWER_Y_SIZE");
    LDDrift_keyWords.emplace_back("PROJECT_MANAGER_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("PROJECT_MANAGER_X_SIZE");
    LDDrift_keyWords.emplace_back("PROJECT_MANAGER_Y_SIZE");
    LDDrift_keyWords.emplace_back("CONSOLE_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("CONSOLE_X_SIZE");
    LDDrift_keyWords.emplace_back("CONSOLE_Y_SIZE");
    LDDrift_keyWords.emplace_back("MAIN_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("MAIN_WINDOW_X_SIZE");
    LDDrift_keyWords.emplace_back("MAIN_WINDOW_Y_SIZE");
    LDDrift_keyWords.emplace_back("CIRCLE_CONFIGURE_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("POLYGON_CONFIGURE_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("LINE_CONFIGURE_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("SET_KEY_TARGET_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("EXIT_WARNING_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("CREATE_NEW_CIRCLE_ACTOR_WINDOW_NAME");
    LDDrift_keyWords.emplace_back("LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_C");
    LDDrift_keyWords.emplace_back("LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_P");
    LDDrift_keyWords.emplace_back("LUCID_DRIFT_ACTOR_GEOMETRY_TYPE_L");
    LDDrift_keyWords.emplace_back("LUCID_DRIFT_SHAPE_RENDER_AS_FILLED");
    LDDrift_keyWords.emplace_back("LUCID_DRIFT_SHAPE_RENDER_AS_OUTLINE");
    LDDrift_keyWords.emplace_back("LD_PLUGIN_API");
    LDDrift_keyWords.emplace_back("NULL_STR_VALUE");
    LDDrift_keyWords.emplace_back("LOWER_BOUND_WHILE_LOOP");
    LDDrift_keyWords.emplace_back("UPPER_BOUND_WHILE_LOOP");
    LDDrift_keyWords.emplace_back("UPPER_BOUND");
    LDDrift_keyWords.emplace_back("NULL_STRING");
}

std::vector<std::string> LDDrift::CodePathfinder::GetSuggestions(const std::string& inputLineText) {
    std::vector<std::string> suggestions;
    if (inputLineText == lastLineInput) {
        return lastSuggestions;
    }
    if (inputLineText.find("std") != std::string::npos && inputLineText.find("LDDrift") != std::string::npos) {
        return suggestions;
    }
    lastLineInput = inputLineText;
    if (inputLineText.find("LDDrift") != std::string::npos) {
        for (const std::string& keyWord : LDDrift_keyWords) {
            if (keyWord.find(inputLineText) != std::string::npos) {
                suggestions.push_back(keyWord);
            }
        }
    }
    if (inputLineText.find("std") != std::string::npos) {
        for (const std::string& keyWord : std_keyWords) {
            if (keyWord.find(inputLineText) != std::string::npos) {
                suggestions.push_back(keyWord);
            }
        }
    }
    lastSuggestions = suggestions;
    return suggestions;
}
