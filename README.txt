This is a simple service container for Drupal 7. Used this idea to build it:
http://dqxtech.net/blog/2014-06-13/simple-do-it-yourself-php-service-container

Usage:

1. Create a module that depends on this module.
2. In your module create a subclass of the AbstractPPContainer class.
3. Add your serivce classes as magic properties, e.g. @property above the class declaration. This helps you IDE to recognize what object it is dealing with.
4. In you main module file create a function that simply returns "container('subclassName')".
5. Call the function in the previous step and chain property names from step 3. to access your services.
6. If you create a new service, you need to replicate step 3. with the new service name.
