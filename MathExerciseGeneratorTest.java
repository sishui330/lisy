import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class MathExerciseGeneratorTest {

    @Test
    void testGenerateExercises() {
        MathExerciseGenerator generator = new MathExerciseGenerator();

        String exerciseGrade1 = generator.generateExercises(1, 2);
        System.out.println("Grade 1 Exercise:");
        System.out.println(exerciseGrade1);
        assertNotNull(exerciseGrade1);
        assertTrue(exerciseGrade1.contains("Exercise 1:"));
        assertTrue(exerciseGrade1.contains("Exercise 2:"));

        String exerciseGrade2 = generator.generateExercises(2, 2);
        System.out.println("Grade 2 Exercise:");
        System.out.println(exerciseGrade2);
        assertNotNull(exerciseGrade2);
        assertTrue(exerciseGrade2.contains("Exercise 1:"));
        assertTrue(exerciseGrade2.contains("Exercise 2:"));

        String exerciseGrade3 = generator.generateExercises(3, 2);
        System.out.println("Grade 3 Exercise:");
        System.out.println(exerciseGrade3);
        assertNotNull(exerciseGrade3);
        assertTrue(exerciseGrade3.contains("Exercise 1:"));
        assertTrue(exerciseGrade3.contains("Exercise 2:"));

        String exerciseGrade4 = generator.generateExercises(4, 2);
        System.out.println("Grade 4 Exercise:");
        System.out.println(exerciseGrade4);
        assertNotNull(exerciseGrade4);
        assertTrue(exerciseGrade4.contains("Exercise 1:"));
        assertTrue(exerciseGrade4.contains("Exercise 2:"));

        String exerciseGrade5 = generator.generateExercises(5, 2);
        System.out.println("Grade 5 Exercise:");
        System.out.println(exerciseGrade5);
        assertNotNull(exerciseGrade5);
        assertTrue(exerciseGrade5.contains("Exercise 1:"));
        assertTrue(exerciseGrade5.contains("Exercise 2:"));

        String exerciseGrade6 = generator.generateExercises(6, 2);
        System.out.println("Grade 6 Exercise:");
        System.out.println(exerciseGrade6);
        assertNotNull(exerciseGrade6);
        assertTrue(exerciseGrade6.contains("Exercise 1:"));
        assertTrue(exerciseGrade6.contains("Exercise 2:"));
    }
}

