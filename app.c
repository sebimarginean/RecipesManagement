#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_RECIPES 100
#define MAX_TITLE_LENGTH 50
#define MAX_DESC_LENGTH 200
#define MAX_INGR_LENGTH 200

typedef struct
{
    char title[MAX_TITLE_LENGTH];
    char description[MAX_DESC_LENGTH];
    char ingredients[MAX_INGR_LENGTH];
    int num_ingredients;
} Recipe;

void print_recipe(Recipe recipe)
{
    printf("Title: %s", recipe.title);
    printf("Description: %s", recipe.description);
    printf("Ingredients: %s", recipe.ingredients);
    printf("\n");
}

void update_file(Recipe *recipes, int num_recipes)
{
    FILE *file = fopen("recipes.txt", "w");
    if (file == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }
    for (int i = 0; i < num_recipes; i++)
    {
        fprintf(file, "%s", recipes[i].title);
        fprintf(file, "%s", recipes[i].description);
        fprintf(file, "%s", recipes[i].ingredients);
    }
    fclose(file);
}

int search_recipe(Recipe *recipes, int num_recipes, char *search_term)
{
    system("cls");
    update_file(recipes, num_recipes);
    int found = 0;
    for (int i = 0; i < num_recipes; i++)
        if (strstr(recipes[i].title, search_term) != NULL)
        {
            print_recipe(recipes[i]);
            found = 1;
        }
    return found;
}

int add_recipe(Recipe *recipes, int num_recipes)
{
    if (num_recipes >= MAX_RECIPES)
    {
        printf("Maximum number of recipes reached\n");
        return num_recipes;
    }

    Recipe new_recipe;
    printf("Enter recipe title: ");
    fgets(new_recipe.title, MAX_TITLE_LENGTH, stdin);
    new_recipe.title[strcspn(new_recipe.title, "\n")] = '\n';
    printf("Enter recipe description: ");
    fgets(new_recipe.description, MAX_DESC_LENGTH, stdin);
    new_recipe.description[strcspn(new_recipe.description, "\n")] = '\n';
    printf("Enter recipe ingredients: ");
    fgets(new_recipe.ingredients, MAX_DESC_LENGTH, stdin);
    new_recipe.ingredients[strcspn(new_recipe.description, "\n")] = '\n';
    recipes[num_recipes] = new_recipe;
    update_file(recipes, num_recipes + 1);
    return num_recipes + 1;
}

int delete_recipe(Recipe *recipes, int num_recipes, char *title)
{
    int index = -1;
    for (int i = 0; i < num_recipes; i++)
    {
        if (strstr(recipes[i].title, title))
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Recipe not found\n");
        return num_recipes;
    }
    for (int i = index; i < num_recipes - 1; i++)
    {
        recipes[i] = recipes[i + 1];
    }
    update_file(recipes, num_recipes - 1);
    printf("Recipe deleted\n");
    return num_recipes - 1;
}

int edit_recipe(Recipe *recipes, int num_recipes, char *title)
{
    int index = -1;
    for (int i = 0; i < num_recipes; i++)
    {
        if (strstr(recipes[i].title, title))
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Recipe not found\n");
        return num_recipes;
    }

    printf("Enter new recipe title: ");
    fgets(recipes[index].title, MAX_TITLE_LENGTH, stdin);
    recipes[index].title[strcspn(recipes[index].title, "\n")] = '\n';
    printf("Enter new recipe description: ");
    fgets(recipes[index].description, MAX_DESC_LENGTH, stdin);
    recipes[index].description[strcspn(recipes[index].description, "\n")] = '\n';
    printf("Enter new recipe ingredients: ");
    fgets(recipes[index].ingredients, MAX_INGR_LENGTH, stdin);
    recipes[index].ingredients[strcspn(recipes[index].description, "\n")] = '\n';
    printf("Recipe edited\n");
    update_file(recipes, num_recipes);
    return num_recipes;
}

int main()
{
    Recipe recipes[MAX_RECIPES];
    int num_recipes = 0;
    int choice;
    char search_term[MAX_TITLE_LENGTH];
    char title[MAX_TITLE_LENGTH];
    FILE *file = fopen("recipes.txt", "r");
    if (file == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }
    char file_title[MAX_TITLE_LENGTH], file_description[MAX_DESC_LENGTH], file_ingredients[MAX_INGR_LENGTH];
    while (fgets(file_title, MAX_DESC_LENGTH, file) != NULL &&
           fgets(file_description, MAX_DESC_LENGTH, file) != NULL &&
           fgets(file_ingredients, MAX_DESC_LENGTH, file) != NULL)
    {
        Recipe recipe;
        strcpy(recipe.title, file_title);
        strcpy(recipe.description, file_description);
        strcpy(recipe.ingredients, file_ingredients);
        recipes[num_recipes++] = recipe;
    }
    do
    {
        printf("Choose an option:\n");
        printf("1. Show all recipies\n");
        printf("2. Search for a recipe\n");
        printf("3. Add a recipe\n");
        printf("4. Delete a recipe\n");
        printf("5. Edit a recipe\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            system("cls");

            for (int i = 0; i < num_recipes; i++)
                print_recipe(recipes[i]);
            system("pause");
            break;
        case 2:
            system("cls");
            printf("Enter search term: ");
            fgets(search_term, MAX_TITLE_LENGTH, stdin);
            search_term[strcspn(search_term, "\n")] = '\0';
            if (!search_recipe(recipes, num_recipes, search_term))
                printf("No recipes found\n");
            system("pause");
            break;
        case 3:
            system("cls");
            num_recipes = add_recipe(recipes, num_recipes);
            printf("Recipe added\n");
            break;
        case 4:
            system("cls");
            printf("Enter title of recipe to delete: ");
            fgets(title, MAX_TITLE_LENGTH, stdin);
            title[strcspn(title, "\n")] = '\0';
            num_recipes = delete_recipe(recipes, num_recipes, title);
            break;
        case 5:
            system("cls");
            printf("Enter title of recipe to edit: ");
            fgets(title, MAX_TITLE_LENGTH, stdin);
            title[strcspn(title, "\n")] = '\0';
            num_recipes = edit_recipe(recipes, num_recipes, title);
            break;
        case 6:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    } while (choice != 6);

    return 0;
}