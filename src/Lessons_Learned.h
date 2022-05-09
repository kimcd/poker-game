
#ifndef Lessons_Learned_h
#define Lessons_Learned_h

/*
 Pointers are use for 3 reasons:
 
 1. to allocate new objects onto the heap
 - objects are placed either in the stack or the heap. when stored in the stack,
 an object is deleted when it goes out of scopr. however, when stored on the heap,
 the object is deleted when the program ends (or until you delete it). so you'd
 use pointers when you want your object to stay around a bit longer
 
 
 2. to pass functions to other functions
 
 3. to iterate over elements within an array or container
 
 
 when to use pionter:
 https://stackoverflow.com/questions/22146094/why-should-i-use-a-pointer-rather-than-the-object-itself
 
 - Polymorphic behavior
 to avoid slicing of derived members!!!!
 
 */

/*
 Some other lessons.
 
 */

/*
 Five_Draw_Table::Five_Draw_Table(const int num_players)
 : players(get_players(num_players)),
 dealer(Dealer()),
 pot(Pot<int>())
 {

 }

 vector<Player> Five_Draw_Table::create_players(const int num_players) const
 {
 vector<Player> players;
 for(int i=0; i<=num_players; ++i)
 {
 players.push_back(Player(i));
 }
 return players;
 }

 VS

 Five_Draw_Table::Five_Draw_Table(const int num_players)
 dealer(Dealer()),
 pot(Pot<int>())
 {
 create_players(num_players);

 }

 void Five_Draw_Table::create_players(const int num_players)
 {
 for(int i=0; i<=num_players; ++i)
 {
 this->players.push_back(Player(i));
 }
 }

 */




/*
 Prefer non-member non-friend functions over methods.
 https://blog.ycshao.com/2017/10/14/effective-c-item-23-prefer-non-member-non-friend-functions-to-member-functions/

 How non-member non-friends improve encapcsulation
 https://stackoverflow.com/questions/1692084/how-non-member-functions-improve-encapsulation

 */

/*
 cerr << "\xe2\x99\xa5" << endl;
 cerr << "\xE2\x99\xA6" << endl;
 cerr << "\xE2\x99\xA0" << endl;
 cerr << "\xE2\x99\xA3" << endl;
 // https://stackoverflow.com/questions/27133508/how-to-print-spades-hearts-diamonds-etc-in-c-and-linux

 */

/*

 This won't work because cout << deck will call the copy constructor.
 That means show_deck() is non-const method.

 void Dealer::show_deck() const
 {
 print_method("show_deck()");

 cout << deck << endl;
 }

 */

/*
 Once I added in methods for copy construction and destruction AND asked for
 messages, I realized that there are a lot of copies and destructions happening
 where I didn't expect. I think it's a good idea to always have a custom
 copy constructor and destructor printing out messages to see when they are
 called.

 */


/* Guide on when to pass by value, reference, pointer
 https://stackoverflow.com/questions/334856/are-there-benefits-of-passing-by-pointer-over-passing-by-reference-in-c#:~:text=Pass%20by%20value%20when%20the%20function%20does%20not%20want%20to%20modify%20the%20parameter%20and%20the%20value%20is%20easy%20to%20copy%20(ints%2C%20doubles%2C%20char%2C%20bool%2C%20etc...%20simple%20types.%20std%3A%3Astring%2C%20std%3A%3Avector%2C%20and%20all%20other%20STL%20containers%20are%20NOT%20simple%20types.)

 */




/*
 When using range-based for loops, if you don't call by reference, objects are
 copied. The problem is that work done on those objects are undone.

 for(Player player : players)
 {
 //do stuff on player is temporary. it will be deleted once it leaves this loop
 }

 for(Player& player : players)
 {
 //do stuff on player is on the actual players.
 }

 Consider always using const and ref. If you need to modify the object than
 just pass by ref.

 See

 https://stackoverflow.com/questions/51387535/c-range-based-for-loop-is-the-container-copied

https://stackoverflow.com/questions/10750057/how-do-i-print-out-the-contents-of-a-vector#:~:text=Regardless%20of%20whether%20you%20use%20the%20explicit%20type%20or%20the%20auto%20keyword%2C%20the%20object%20i%20has%20a%20value%20that%20is%20a%20copy%20of%20the%20actual%20item%20in%20the%20path%20object.%20Thus%2C%20all%20changes%20to%20i%20in%20the%20loop%20are%20not%20preserved%20in%20path%20itself%3A

 */

/*
 When working with dynamic containers, like vectors, always .reserve() and .emplace_back()
 over push_back(). Push_back() will cause copies no matter whether you reserve
 or not. https://zpjiang.me/2018/08/08/Copy-Constructor-and-std-vector-emplace-back/

 https://stackoverflow.com/questions/32199388/what-is-better-reserve-vector-capacity-preallocate-to-size-or-push-back-in-loo

 */


/*
 When working with std::vector::erase(), erasing from anywhere other than back
 will actually reallocate all elements after the segment. This is why in
 Deck::top_card(), I erase the last Card.

 https://www.cplusplus.com/reference/vector/vector/erase/#:~:text=Because%20vectors%20use,list%20or%20forward_list).

 */

#endif /* Lessons_Learned_h */
