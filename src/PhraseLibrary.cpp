#include "PhraseLibrary.h"
#include <cstdlib>
#include <ctime>

PhraseLibrary::PhraseLibrary() : lastEasyIndex(-1), lastHardIndex(-1) {
    std::srand(std::time(nullptr));

    // EASY PHRASES
    easyPhrase = {
        // FOOD
        {"CHOCOLATE CAKE", "Food", {"Sweet dessert", "Made from cocoa", "Popular birthday treat"}},
        {"APPLE PIE", "Food", {"Classic Fall dessert", "Often served with ice cream", "Made with fruit filling"}},
        {"PEPPERONI PIZZA", "Food", {"Italian dish", "Often round in shape", "Baked in oven"}},
        {"MAC AND CHEESE", "Food", {"Cheesy comfort food", "Pasta dish", "Can be baked"}},
        {"STRAWBERRY JAM", "Food", {"Spreadable fruit", "Made from berries", "Sweet taste"}},
        {"CHOCOLATE CHIP COOKIE", "Food", {"Baked treat", "Has chocolate chunks", "Often a circular shape"}},
        {"FRUIT SALAD", "Food", {"Mix of fruits", "Healthy option", "Often served chilled"}},

        // ANIMAL
        {"POLAR BEAR", "Animal", {"Arctic animal", "White fur", "Largest land carnivore"}},
        {"ORANGE CAT", "Animal", {"Domestic pet", "Cartoon charcater Garfield", "Often orange colored"}},
        {"BLUE WHALE", "Animal", {"Largest animal on Earth", "Lives in ocean", "Makes loud sounds"}},
        {"GRAY WOLF", "Animal", {"Lives in packs", "Gray fur", "Carnivorous mammal"}},
        {"SEA TURTLE", "Animal", {"Marine reptile", "Lives in ocean", "Can live long"}},
        {"GOLDEN RETRIEVER", "Animal", {"Friendly dog breed", "Golden fur", "Good family pet"}},

        // MOVIE TITLE
        {"TOY STORY", "Movie Title", {"Animated movie", "Buzz and Woody", "Toys come to life"}},
        {"JURASSIC PARK", "Movie Title", {"Dinosaurs", "Adventure film", "Directed by Spielberg"}},
        {"HARRY POTTER", "Movie Title", {"Wizard story", "Magic school", "Famous books adaptation"}},
        {"TANGLED", "Movie Title", {"Story about long hair", "Disney animation", "Rapunzel"}},
        {"THE LION KING", "Movie Title", {"Disney classic", "Lion protagonist", "Africa setting"}},
        {"FINDING NEMO", "Movie Title", {"Clownfish", "Ocean adventure", "Father searches for son"}},
        {"MONSTERS INC", "Movie Title", {"One eyed monster", "Funny monsters", "Pixar animation"}},
        {"THE LITTLE MERMAID", "Movie Title", {"Mermaid protagonist", "Main character wants to be human", "Underwater story"}},

        // SONG TITLE
        {"SHAKE IT OFF", "Song Title", {"Taylor Swift hit", "Pop genre", "About ignoring critics"}},
        {"COUNTING STARS", "Song Title", {"OneRepublic hit", "Pop-rock genre", "About dreams and money"}},
        {"SHAPE OF YOU", "Song Title", {"Ed Sheeran hit", "Pop song", "Danceable tune"}},
        {"FIREWORK", "Song Title", {"Katy Perry song", "Inspirational lyrics", "Pop genre"}},
        {"LET IT GO", "Song Title", {"Frozen movie song", "Disney", "Powerful female vocals"}},
        {"BLANK SPACE", "Song Title", {"Taylor Swift", "Pop hit", "Satirical love song"}},
        {"HEY BROTHER", "Song Title", {"Avicii song", "Electronic music", "Family-themed lyrics"}},
        {"DON'T YOU WORRY CHILD", "Song Title", {"Swedish House Mafia", "EDM hit", "Emotional lyrics"}},
        {"UNDER CONTROL", "Song Title", {"Calvin Harris", "EDM track", "Upbeat dance song"}},
        {"MIRACLE MAKER", "Song Title", {"By Dom Dolla", "House music genre", "Uplifting lyrics"}},
        {"HAVANA", "Song Title", {"Camila Cabello", "Cuban influence", "Pop hit"}},
        {"FEEL SO CLOSE", "Song Title", {"Calvin Harris track", "Dance song", "Electronic music"}},
        {"HEADLINES", "Song Title", {"Drake song", "Hip-hop", "Catchy lyrics"}},
        {"DIE YOUNG", "Song Title", {"Ke$ha hit", "Party song", "Upbeat tempo"}},
        {"AM I WRONG", "Song Title", {"Nico & Vinz", "Pop song", "Motivational lyrics"}},
        {"RHYTHM AS A DANCER", "Song Title", {"Snap!", "80s hit", "Dance song"}},
        {"TELEPHONE", "Song Title", {"Lady Gaga", "Pop hit", "Collab with Beyoncé"}},
        {"LEAN ON ME", "Song Title", {"Church Song", "Inspirational", "Helping friends"}},
        {"LEAN ON", "Song Title", {"Major Lazer", "Electronic", "Collaborative track"}},

        // COUNTRIES
        {"ITALY", "Country", {"Famous for pasta", "Rome is the capital", "Home of the Colosseum"}},
        {"POLAND", "Country", {"Eastern Europe", "Warsaw capital", "Famous for pierogi"}},
        {"SOUTH KOREA", "Country", {"Capital Seoul", "K-pop music", "Technologically advanced"}},
        {"GREECE", "Country", {"Olympic origins", "Athens capital", "Famous islands"}},
        {"SWITZERLAND", "Country", {"Neutral country", "Alps mountains", "Famous for chocolate"}},
        {"AUSTRALIA", "Country", {"Sydney Opera House", "Kangaroos", "Southern hemisphere"}},

        // PLACE
        {"AMUSEMENT PARK", "Place", {"Roller coasters", "Fun rides", "Often has cotton candy"}},
        {"THE ZOO", "Place", {"Animals to see", "Educational trips", "Often for families"}},
        {"THE BEACH", "Place", {"Sand and water", "Sunbathing", "Swimming activities"}},
        {"MOVIE THEATER", "Place", {"Big screen", "Popcorn snacks", "Watch films"}},
        {"COFFEE SHOP", "Place", {"Hot beverages", "Relaxing spot", "Often Wi-Fi available"}},
        {"WESTERN UNIVERSITY", "Place", {"Educational institution", "Ontario location", "Campus life"}},
        {"TRAMPOLINE PARK", "Place", {"Jumping activity", "Indoor fun", "Exercise and play"}},

        // QUOTATION
        {"PRACTICE MAKES PERFECT", "Quotation", {"Encourages repetition", "Learning advice", "Famous proverb"}},
        {"BETTER LATE THAN NEVER", "Quotation", {"Timing advice", "Don't procrastinate", "Common saying"}},
        {"KNOWLEDGE IS POWER", "Quotation", {"Famous saying", "Educational", "Importance of learning"}},
        {"YOU ONLY LIVE ONCE", "Quotation", {"YOLO", "Live life fully", "Popular phrase"}},
        {"HOME SWEET HOME", "Quotation", {"Comfort of home", "Family place", "Well-known proverb"}},
        {"NEVER SAY NEVER", "Quotation", {"Motivational", "Persistence advice", "Popular saying"}},
        {"THE EARLY BIRD GETS THE WORM", "Quotation", {"Wake up early", "Productivity advice", "Common proverb"}},
        {"OUT OF SIGHT OUT OF MIND", "Quotation", {"Forget easily", "Not nearby", "What you don't know can't harm you"}},

        // THING
        {"RED BALLOON", "Thing", {"Round in shape", "Appears in the movie 'IT'", "Can float"}},
        {"WATER BOTTLE", "Thing", {"Container for liquids", "Portable", "Reusable"}},
        {"TEDDY BEAR", "Thing", {"Soft toy", "Resembles an animal", "Stuffed animal"}},
        {"SUNGLASSES", "Thing", {"Protects eyes", "Worn outdoors", "Fashion accessory"}},
        {"COMPUTER MOUSE", "Thing", {"Input device", "Connected to computer", "Hand-held"}},
        {"PAINTBRUSH", "Thing", {"Used in painting", "Holds paint", "Art tool"}},
        {"UMBRELLA", "Thing", {"Rain protection", "Portable", "Collapsible"}},
        {"SKATEBOARD", "Thing", {"Rolling board", "Sporting activity", "Trick performance"}},
        {"HEADPHONES", "Thing", {"Audio device", "Over ears or in ears", "Listen to music"}},
        {"CANDLE", "Thing", {"Wax object", "Provides light", "Often scented"}},

        // ARTISTS
        {"JUSTIN BIEBER", "Artist", {"Pop singer", "Canadian", "Famous since 2009"}},
        {"TAYLOR SWIFT", "Artist", {"Country and pop singer", "Known for her song 'Love Story'", "Engaged to an NFL Player"}},
        {"KATY PERRY", "Artist", {"Pop singer", "Colorful performances", "California Dreams"}},
        {"SELENA GOMEZ", "Artist", {"Pop singer", "Actress", "Disney Channel star"}},
        {"ARIANA GRANDE", "Artist", {"Pop singer", "High vocal range", "Famous for ponytail"}},
        {"BRUNO MARS", "Artist", {"Pop/R&B singer", "Performs live", "Hit songs"}},
        {"ED SHEERAN", "Artist", {"Singer-songwriter", "Guitarist", "Hit song Shape of You"}}
    };

    // HARD PHRASES
    hardPhrase = {
        // FOOD
        {"PAPIYA", "Food", {"Tropical fruit", "Sweet and juicy", "Often yellowish-orange"}},
        {"POMMAGRANTE", "Food", {"Fruit with seeds", "Juicy red inside", "Used in salads"}},
        {"ELDERBERRY", "Food", {"Dark berry", "Used in syrups", "Rich in antioxidants"}},
        {"CHICKEN SOUVLAKI", "Food", {"Greek dish", "Grilled meat", "Served with pita"}},
        {"BRUSCHETTA", "Food", {"Italian appetizer", "Toasted bread", "Topped with tomatoes"}},
        {"CHARCUTERIE", "Food", {"Assortment of meats", "Served as appetizer", "French origin"}},
        {"GNOCCHI", "Food", {"Italian pasta", "Potato-based", "Soft dumplings"}},
        {"ESCARGOT", "Food", {"French cuisine", "Often served in garlic butter", "Edible snails"}},
        {"MASCARPONE CHEESE", "Food", {"Italian cheese", "Used in desserts", "Soft and creamy"}},
        {"BUCKWHEAT", "Food", {"Grain-like seed", "Used in pancakes", "Gluten-free option"}},
        {"TIRAMISU", "Food", {"Italian dessert", "Coffee-flavored", "Layered with mascarpone"}},

        // ANIMAL
        {"HIPPOPOTAMUS", "Animal", {"Large African mammal", "Spends time in water", "Herbivore"}},
        {"CATERPILLAR", "Animal", {"Larval stage", "Becomes butterfly", "Soft body"}},
        {"ORANGUTAN", "Animal", {"Large ape", "Lives in trees", "Red fur"}},
        {"CHIMPANZEE", "Animal", {"Intelligent ape", "Lives in Africa", "Uses tools"}},
        {"RHINOCEROS", "Animal", {"Horned mammal", "Thick skin", "Large herbivore"}},
        {"TASMANIAN DEVIL", "Animal", {"Australian marsupial", "Aggressive", "Black fur"}},
        {"TARANTULA", "Animal", {"Large spider", "Hairy body", "Venomous bite"}},

        // MOVIE TITLE
        {"PIRATES OF THE CARIBBEAN", "Movie Title", {"Johnny Depp stars", "Jack Sparrow", "Pirates"}},
        {"THE LORD OF THE RINGS", "Movie Title", {"Fantasy epic", "Frodo journey", "Based on Tolkien books"}},
        {"THE CHRONICLES OF NARNIA", "Movie Title", {"Fantasy world", "Children enter wardrobe", "Magical creatures"}},
        {"A STREETCAR NAMED DESIRE", "Movie Title", {"Classic play adaptation", "Tennessee Williams", "Drama"}},
        {"HOW TO TRAIN YOUR DRAGON", "Movie Title", {"Animated film", "Viking boy", "Dragon companion"}},
        {"THE SECRET LIFE OF PETS", "Movie Title", {"Animated comedy", "Pets' adventures", "City setting"}},
        {"SPIDERMAN INTO THE SPIDERVERSE", "Movie Title", {"Multiple Spider-Men", "Animated film", "Superhero story"}},

        // SONG TITLE
        {"SMELLS LIKE TEEN SPIRIT", "Song Title", {"Nirvana song", "1990s grunge", "Famous guitar riff"}},
        {"VIVA LA VIDA", "Song Title", {"Coldplay song", "Orchestral pop", "Historical references"}},
        {"STAIRWAY TO HEAVEN", "Song Title", {"Led Zeppelin song", "Classic rock", "Epic guitar solo"}},
        {"ANOTHER ONE BITES THE DUST", "Song Title", {"Queen song", "Funk rock", "Bass-driven track"}},
        {"BOHEMIAN RHAPSODY", "Song Title", {"Queen hit", "Operatic sections", "Famous music video"}},
        {"SINCE U BEEN GONE", "Song Title", {"Kelly Clarkson", "Pop-rock", "Breakup anthem"}},
        {"SOMEBODY THAT I USED TO KNOW", "Song Title", {"Gotye song", "Duet", "Heartbreak theme"}},
        {"WHAT A WONDERFUL WORLD", "Song Title", {"Louis Armstrong", "Classic song", "Optimistic lyrics"}},
        {"LA DANZA", "Song Title", {"By John Summit", "Summery/Vacation Song", "Dance/Electornic Genre"}},
        {"WATCH THE SUNRISE", "Song Title", {"By Chris Lake", "Cheerful house music mix", "On his album 'Chemistry'"}},
        {"HOW TO SAVE A LIFE", "Song Title", {"The Fray", "Piano-driven song", "Storytelling lyrics"}},
        {"POCKETFUL OF SUNSHINE", "Song Title", {"Natasha Bedingfield", "Pop anthem", "'Sunshine'"}},
        {"SWEET DEPOSITION", "Song Title", {"Remix of the Australian band The Temper Trap", "House music", "John Summit"}},
        {"GUATEMALA", "Song Title", {"Named after a Central American country", "Released in 2018", "Performed by Rae Sremmurd, including Swae Lee and Slim Jxmmi"}},

        // COUNTRIES
        {"BOSNIA AND HERZEGOVINA", "Country", {"Balkan country", "Capital is Sarajevo", "Known for mountains"}},
        {"CZECH REPUBLIC", "Country", {"Central Europe", "Capital Prague", "Famous castles"}},
        {"UNITED ARAB EMIRATES", "Country", {"Middle East", "Dubai city", "Desert and skyscrapers"}},
        {"TRINIDAD AND TOBAGO", "Country", {"Caribbean", "Famous for Carnival", "Two islands"}},
        {"NORTH MACEDONIA", "Country", {"Balkan country", "Capital Skopje", "Historic sites"}},
        {"EL SALVADOR", "Country", {"Central America", "Capital San Salvador", "Known for volcanoes"}},
        {"DEMOCRATIC REPUBLIC OF THE CONGO", "Country", {"African country", "Capital Kinshasa", "Rainforest region"}},
        {"VATICAN CITY", "Country", {"Smallest country", "Inside Rome", "Pope resides here"}},
        {"LIECHTENSTEIN", "Country", {"Tiny European country", "Between Switzerland and Austria", "Alpine landscape"}},

        // PLACE
        {"MOUNT EVEREST", "Place", {"Tallest mountain", "Located in Himalayas", "Climbers dream"}},
        {"THE SAHARA DESERT", "Place", {"World's largest desert", "North Africa", "Sand dunes"}},
        {"EIFFEL TOWER", "Place", {"Paris landmark", "Iron structure", "Tourist attraction"}},
        {"NIAGARA FALLS", "Place", {"Waterfalls", "Border USA/Canada", "Famous tourist site"}},
        {"THE GREAT WALL OF CHINA", "Place", {"Ancient fortification", "Visible from space myth", "China"}},
        {"AMAZON RAINFOREST", "Place", {"South America", "Dense jungle", "Biodiversity hotspot"}},
        {"MOUNT KILIMANJARO", "Place", {"Tallest African mountain", "Volcano", "Located in Tanzania"}},
        {"MIDDLESEX COLLEGE", "Place", {"University", "Campus buildings", "Ontario, Canada"}},

        // QUOTATION
        {"TO BE OR NOT TO BE THAT IS THE QUESTION", "Quotation", {"Hamlet quote", "Shakespeare", "Famous soliloquy"}},
        {"I THINK THEREFORE I AM", "Quotation", {"Philosophy", "Descartes", "Cogito ergo sum"}},

        // THING
        {"ELECTRIC GUITAR", "Thing", {"Musical instrument", "Has strings", "Used in rock music"}},
        {"VINTAGE CAMERA", "Thing", {"Old camera", "Film-based", "Collectible item"}},
        {"SEWING MACHINE", "Thing", {"Stitching device", "Fabric crafting", "Often mechanical"}},
        {"VINYL RECORD", "Thing", {"Music medium", "Rotating disc", "Classic sound"}},
        {"BINOCULARS", "Thing", {"Magnifying device", "Used for viewing", "Hand-held optics"}},
        {"HARMONICA", "Thing", {"Small instrument", "Played with mouth", "Blues music"}} ,

        // ARTISTS
        {"MICHAEL JACKSON", "Artist", {"King of Pop", "Thriller album", "Famous dancer"}},
        {"ELVIS PRESLEY", "Artist", {"King of Rock", "Graceland home", "Famous singer"}},
        {"WHITNEY HOUSTON", "Artist", {"Powerful vocals", "I Will Always Love You", "Pop icon"}},
        {"CELINE DION", "Artist", {"Canadian singer", "Titanic theme song", "Powerful ballads"}},
        {"JOHN SUMMIT", "Artist", {"Electronic DJ", "House music", "Festival performer"}},
        {"ODD MOB", "Artist", {"Australian duo", "Electronic music", "Popular in festivals"}},
        {"AYYBO", "Artist", {"Electronic artist", "Dance tracks", "Performed at VELD Sirkus stage in 2025"}},
        {"DOM DOLLA", "Artist", {"House DJ", "Australian", "Known for his hit song Girl$"}}
    };

    lastEasyIndex = -1;
    lastHardIndex = -1;
}

Phrase PhraseLibrary::getRandomPhrase(const std::string &difficulty) {
    if (difficulty == "easy" && !easyPhrase.empty()) {
        int index;
        do {
            index = std::rand() % easyPhrase.size();
        } while (index == lastEasyIndex && easyPhrase.size() > 1);
        lastEasyIndex = index;
        return easyPhrase[index];
    }
    else if (difficulty == "hard" && !hardPhrase.empty()) {
        int index;
        do {
            index = std::rand() % hardPhrase.size();
        } while (index == lastHardIndex && hardPhrase.size() > 1);
        lastHardIndex = index;
        return hardPhrase[index];
    }
    else {
        return {"No Phrases Available", "None", {}};
    }
}
