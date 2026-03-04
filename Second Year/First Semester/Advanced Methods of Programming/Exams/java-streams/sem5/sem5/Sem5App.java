package ubb.scs.map.sem5;

import java.time.LocalDate;
import java.util.AbstractMap;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Sem5App {
    /**
     * * 1. Lista studentilor care contin un anumit string (parametru), sortati descrescator
     * in functie de media lor
     */
    public static void report1(List<Nota> note, String string) {
        Map<Student, List<Nota>> studentsGrades = note
                .stream()
                .collect(Collectors.groupingBy(Nota::getStudent));
        studentsGrades.entrySet()
                .stream()
                .filter(x -> x.getKey().getName().contains(string))
                .sorted((o1, o2) -> {
                    double avg1 = average(o1.getValue());
                    double avg2 = average(o2.getValue());
                    return -Double.compare(avg1, avg2);
                })
                .forEach(x -> System.out.println(x.getKey().getName() + "; media: " + average(x.getValue())));
    }

    private static double average(List<Nota> notaList) {
        double sum = notaList.stream()
                .map(Nota::getValue)
                .reduce(0d, Double::sum);
        return sum / notaList.size();
    }

    public static void report1Better(List<Nota> note, String string) {
        Map<Student, Double> studentAverages = note.stream()
                .collect(Collectors.groupingBy(
                        Nota::getStudent,
                        Collectors.averagingDouble(Nota::getValue)
                ));

        studentAverages.entrySet().stream()
                .filter(e -> e.getKey().getName().toLowerCase().contains(string.toLowerCase()))
                .sorted(Map.Entry.<Student, Double>comparingByValue().reversed())
                .forEach(e -> System.out.println(e.getKey().getName() + "; media: " + e.getValue()));

    }

    /**
     * 2. Lista profesorilor care contin un anumit string (parametru),
     * sortati descrescator in functie de media notelor date.
     */
    private static void report2(List<Nota> gradesList, String str) {
        Map<String, Double> profesori = gradesList.stream()
                .filter(x -> x.getProfesor().contains(str))
                .collect(Collectors.groupingBy(Nota::getProfesor, Collectors.averagingDouble(Nota::getValue)))
                .entrySet()
                .stream()
                .sorted(Collections.reverseOrder(Map.Entry.comparingByValue()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (value1, _) -> value1, LinkedHashMap::new));
        //try without (value1, _) -> value1, LinkedHashMap::new) first -> sorted useless
        System.out.println(profesori);
    }

    /**
     * 3. Temele de la o anumita grupa (parametru), sortate descrescator in functie * de numarul studentilor care au primit nota la acea materie *
     */
    public static void report3(List<Nota> gradeList, int group) {
        gradeList = gradeList.stream().filter(g -> g.getStudent().getGroup() == group)
                .collect(Collectors.toList());
        Map<Student, List<Nota>> grouped = gradeList.stream()
                .collect(Collectors.groupingBy(Nota::getStudent));
        Stream<Entry<Student, Integer>> gradeCountStream = grouped.entrySet()
                .stream()
                .map(x -> new AbstractMap.SimpleEntry<>(x.getKey(), x.getValue().size()));
        Stream<Map.Entry<Student, Integer>> sorted =
                gradeCountStream.sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()));
        sorted.forEach(x -> System.out.println(x.getKey() + " " + x.getValue()));
    }

    public static void report3Better(List<Nota> gradeList, int group) {
        gradeList.stream()
                .filter(n -> n.getStudent().getGroup() == group)
                .collect(Collectors.groupingBy(
                        Nota::getStudent,
                        Collectors.counting()
                ))
                .entrySet()
                .stream()
                .sorted(Map.Entry.<Student, Long>comparingByValue().reversed())
                .forEach(e ->
                        System.out.println(e.getKey().getName() + " -> număr note: " + e.getValue())
                );
    }

    //4. Lista grupelor care incep cu un anumit numar si media notelor primite de
    // studentii acestora.
    // (Afisarea acestor medii si numerele grupei)
    private static void report4(List<Nota> gradeList, String startNumber) {
        Map<Integer, List<Nota>> groups = gradeList.stream().
                collect(Collectors.groupingBy(x -> x.getStudent().getGroup()));
        Map<Integer, Double> selectedGroups =
                groups.entrySet().stream()
                        .filter(x -> x.getKey().toString().startsWith(startNumber))
                        .map(x -> {
                            double medie = x.getValue().stream().map(y -> y.getValue())
                                    .reduce(0d, (a, b) -> a + b);
                            medie = medie / x.getValue().size();
                            return new AbstractMap.SimpleEntry<Integer, Double>(x.getKey(), medie);
                        })
                        .sorted(Map.Entry.<Integer, Double>comparingByValue().reversed())
                        .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (value1, _) -> value1, LinkedHashMap::new));
        selectedGroups.entrySet().forEach(System.out::println);
    }

    private static void report4Better(List<Nota> gradeList, String startNumber) {
        gradeList.stream()
                .collect(Collectors.groupingBy(
                        n -> n.getStudent().getGroup(),
                        Collectors.averagingDouble(Nota::getValue)
                ))
                .entrySet()
                .stream()
                .filter(e -> String.valueOf(e.getKey()).startsWith(startNumber))
                .sorted(Map.Entry.<Integer, Double>comparingByValue().reversed())
                .forEach(e ->
                        System.out.println("Grupa " + e.getKey() + " -> media notelor: " + e.getValue())
                );
    }

    private static void report5(List<Nota> gradeList) {
        gradeList.stream()
                .collect(Collectors.groupingBy(
                        n -> n.getStudent().getGroup()
                ))
                .entrySet()
                .stream()
                .map(entry -> {
                    Integer group = entry.getKey();
                    List<Nota> notes = entry.getValue();

                    double avgGrade = notes.stream()
                            .mapToDouble(Nota::getValue)
                            .average()
                            .orElse(0);

                    long distinctStudents = notes.stream()
                            .map(n -> n.getStudent().getName())
                            .distinct()
                            .count();

                    double raport = distinctStudents == 0 ? 0 : avgGrade / distinctStudents;
                    return new AbstractMap.SimpleEntry<>(group, raport);
                })
                .sorted(Map.Entry.<Integer, Double>comparingByValue().reversed())
                .forEach(e ->
                        System.out.println("Grupa " + e.getKey() + " -> raport medie/student: " + e.getValue())
                );
    }


    public static void main(String[] args) {
        List<Nota> note = getNote(getStudents(), getTeme());
        //report1(note, "");
        //report2(note, "");
        //report3(note, 221);
        //report3Better(note, 221);
        //report4(note, "2");
        //report4Better(note, "2");
        report5(note);
    }

    private static List<Student> getStudents() {
        Student s1 = new Student("andrei", 221);
        s1.setId(1L);
        Student s2 = new Student("dan", 222);
        s2.setId(2L);
        Student s3 = new Student("gigi", 221);
        s3.setId(3L);
        Student s4 = new Student("costel", 222);
        s4.setId(4L);
        return Arrays.asList(s1, s2, s3, s4);
    }

    private static List<Tema> getTeme() {
        return Arrays.asList(
                new Tema("t1", "desc1"),
                new Tema("t2", "desc2"),
                new Tema("t3", "desc3"),
                new Tema("t4", "desc4")
        );
    }

    private static List<Nota> getNote(List<Student> stud, List<Tema> teme) {
        return Arrays.asList(
                new Nota(stud.get(0), teme.get(0), 10d, LocalDate.of(2019, 11, 2), "profesor1"),
                new Nota(stud.get(1), teme.get(0), 9d, LocalDate.of(2019, 11, 2).minusWeeks(1), "profesor1"),
                new Nota(stud.get(1), teme.get(1), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Nota(stud.get(1), teme.get(2), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Nota(stud.get(2), teme.get(1), 7d, LocalDate.of(2019, 10, 28), "profesor1"),
                new Nota(stud.get(2), teme.get(3), 9d, LocalDate.of(2019, 10, 27), "profesor2"),
                new Nota(stud.get(1), teme.get(3), 10d, LocalDate.of(2019, 10, 29), "profesor2")
        );
    }
}
