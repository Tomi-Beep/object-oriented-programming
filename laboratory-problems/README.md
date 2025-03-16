# Laboratory Problems

## Problem 1: Managing Basketball Players

### Class `BasketballPlayer`
The `BasketballPlayer` class stores information about a basketball player and includes the following fields:

- **Name**: An array of characters (not longer than 20 characters).
- **Surname**: An array of characters (not longer than 20 characters).
- **Jersey Number**: Integer.
- **Points from First Match**: Integer.
- **Points from Second Match**: Integer.
- **Points from Third Match**: Integer.

#### Method `averagePoints()`
This method calculates the average points scored by the basketball player across all three matches.

#### Method `printDetails()`
Prints the details of the basketball player in the following format:
```plaintext
Player: [name] [surname] with number: [jersey number] has [average points] points on average.
```

## Problem 2: Managing Country Data

### Class `Country`
The `Country` class stores information about a country and includes the following fields:

- **Name**: A string of maximum 100 characters representing the name of the country.
- **Capital**: A string of maximum 100 characters representing the capital city.
- **Area**: A decimal number representing the area in thousands of square kilometers.
- **Population**: A decimal number representing the population in millions.

All variables in the class are private.

#### Methods to Implement

1. **Constructors**
   - A constructor with parameters to initialize all fields.
   - A default constructor with no parameters.

2. **Destructor**
   - A destructor to handle cleanup when an object is destroyed.

3. **Set Methods**
   - Set methods for each field to update their values.

4. **Get Methods**
   - Get methods for each field to retrieve their values.

5. **`display()` Method**
   - Prints the details of the country in the following format:
     ```plaintext
     Country: [name]
     Capital: [capital]
     Area: [area]
     Population: [population]
     ```

### Additional Function (Outside the Class)

#### Function `sortCountries`
This function takes an array of `Country` objects and the number of elements in the array as arguments. It sorts the countries in ascending order based on their area.

**Note:** Do not modify the main function.

## Problem 3: Managing Space Data

### Class `SpaceObject`
The `SpaceObject` class stores information about a space object and includes the following fields:

- **Name**: An array of maximum 100 characters representing the name of the space object.
- **Type**: An array of maximum 100 characters representing the type of the space object.
- **DistanceFromEarth**: An integer representing the distance of the object from Earth in light years.

All variables in the class are private.

#### Methods to Implement

1. **Constructors**
   - A constructor with parameters to initialize all fields.
   - A default constructor with no parameters.

2. **Destructor**
   - A destructor to handle cleanup when an object is destroyed.

3. **Set Methods**
   - Set methods for each field to update their values.

4. **Get Methods**
   - Get methods for each field to retrieve their values.

5. **`print()` Method**
   - Prints the details of the space object in the following format:
     ```plaintext
     [name] ([type]) - distance: [distanceFromEarth] light years away from Earth
     ```

---

### Class `Alien`
The `Alien` class stores information about an alien and includes the following fields:

- **Name**: An array of maximum 100 characters representing the name of the alien.
- **Age**: An integer representing the age of the alien.
- **HomePlanet**: An array of maximum 100 characters representing the alien's home planet.
- **NumObj**: An integer representing the number of favorite space objects.
- **SpaceObjects**: An array of `SpaceObject` objects representing the alien's favorite space objects.

All variables in the class are private.

#### Methods to Implement

1. **Constructors**
   - A constructor with parameters to initialize all fields.
   - A default constructor with no parameters.

2. **Destructor**
   - A destructor to handle cleanup when an object is destroyed.

3. **Set Methods**
   - Set methods for each field to update their values.

4. **Get Methods**
   - Get methods for each field to retrieve their values.

5. **Copy Constructor**
   - A copy constructor to create a deep copy of an `Alien` object.

6. **`getObjectClosestToEarth()` Method**
   - Returns the `SpaceObject` from the alien's favorites that has the smallest `distanceFromEarth`.

7. **`print()` Method**
   - Prints the details of the alien in the following format:
     ```plaintext
     Alien name: [name]
     Alien age: [age]
     Alien homePlanet: [homePlanet]
     Favourite space object closest to Earth: [object details]
     ```

---

### Implementation Notes

- All fields should remain private, and their values should be accessed or modified through the provided methods.
- Ensure proper memory management in constructors, destructors, and the copy constructor.

---

### Additional Instructions

- Do not modify the `main()` function.
- Ensure the implementation adheres to the specified formats for printing and sorting.

