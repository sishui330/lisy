import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

public class MathExerciseGenerator extends JFrame implements ActionListener {
    private JLabel countLabel, exerciseLabel;
    private JComboBox<Character> operatorComboBox; // 运算符选择框
    private JTextField maxNumberField, countTextField; // 最大数文本框、题目数量文本框
    private JCheckBox bracketsCheckBox, decimalCheckBox; // 括号复选框、小数复选框
    private JTextArea exerciseTextArea; // 题目文本区域
    private JButton generateButton, outputFileButton; // 生成按钮、输出到文件按钮

    public MathExerciseGenerator() {
        setTitle("Math Exercise Generator"); // 设置窗口标题
        setLayout(new BorderLayout()); // 设置布局为边界布局

        JPanel controlPanel = new JPanel(new GridLayout(7, 2, 10, 10)); // 控制面板，使用网格布局
        controlPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10)); // 设置边距

        countLabel = new JLabel("题目数量:"); // 题目数量标签
        controlPanel.add(countLabel);
        countTextField = new JTextField(10); // 题目数量文本框
        controlPanel.add(countTextField);

        JLabel operatorLabel = new JLabel("选择运算符:"); // 运算符标签
        controlPanel.add(operatorLabel);
        operatorComboBox = new JComboBox<>(new Character[]{'+', '-', '*', '/'}); // 运算符选择框
        controlPanel.add(operatorComboBox);

        JLabel maxNumberLabel = new JLabel("最大数:"); // 最大数标签
        controlPanel.add(maxNumberLabel);
        maxNumberField = new JTextField(10); // 最大数文本框
        controlPanel.add(maxNumberField);

        bracketsCheckBox = new JCheckBox("包含括号"); // 括号复选框
        controlPanel.add(bracketsCheckBox);
        decimalCheckBox = new JCheckBox("包含小数"); // 小数复选框
        controlPanel.add(decimalCheckBox);

        generateButton = new JButton("生成题目"); // 生成按钮
        generateButton.addActionListener(this); // 添加事件监听器
        controlPanel.add(generateButton);

        outputFileButton = new JButton("输出到文件"); // 输出到文件按钮
        outputFileButton.addActionListener(this); // 添加事件监听器
        controlPanel.add(outputFileButton);

        add(controlPanel, BorderLayout.NORTH); // 将控制面板添加到窗口的北部

        exerciseLabel = new JLabel("题目:"); // 题目标签
        add(exerciseLabel, BorderLayout.WEST);

        exerciseTextArea = new JTextArea(20, 30); // 题目文本区域
        exerciseTextArea.setEditable(false); // 不可编辑
        JScrollPane scrollPane = new JScrollPane(exerciseTextArea); // 添加滚动条
        add(scrollPane, BorderLayout.CENTER); // 将题目文本区域添加到窗口的中间

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // 设置关闭操作
        pack(); // 自动调整大小
        setLocationRelativeTo(null); // 居中显示
        setVisible(true); // 显示窗口
    }

    // 按钮事件处理
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == generateButton) { // 如果点击了生成按钮
            generateExercises(); // 生成题目
        } else if (e.getSource() == outputFileButton) { // 如果点击了输出到文件按钮
            outputToFile(); // 输出到文件
        }
    }

    // 生成题目方法
    void generateExercises() {
        try {
            int count = Integer.parseInt(countTextField.getText()); // 获取题目数量
            char operator = (char) operatorComboBox.getSelectedItem(); // 获取运算符
            int maxNumber = Integer.parseInt(maxNumberField.getText()); // 获取最大数
            boolean withBrackets = bracketsCheckBox.isSelected(); // 是否包含括号
            boolean withDecimal = decimalCheckBox.isSelected(); // 是否包含小数

            Random random = new Random();
            StringBuilder exercises = new StringBuilder();

            for (int i = 0; i < count; i++) {
                int operand1 = random.nextInt(maxNumber) + 1; // 随机数1
                int operand2 = random.nextInt(maxNumber) + 1; // 随机数2

                if (withDecimal) { // 如果包含小数
                    double doubleOperand1 = random.nextDouble() * maxNumber; // 随机小数1
                    double doubleOperand2 = random.nextDouble() * maxNumber; // 随机小数2
                    exercises.append(String.format("%.2f %c %.2f =  \n", doubleOperand1, operator, doubleOperand2)); // 格式化输出
                } else {
                    if (withBrackets) { // 如果包含括号
                        exercises.append(String.format("(%d %c %d) =  \n", operand1, operator, operand2)); // 格式化输出
                    } else {
                        exercises.append(String.format("%d %c %d =  \n", operand1, operator, operand2)); // 格式化输出
                    }
                }
            }

            exerciseTextArea.setText(exercises.toString()); // 设置题目文本区域内容
        } catch (NumberFormatException ex) { // 异常处理
            exerciseTextArea.setText("请输入有效的数字！");
        }
    }

    // 输出到文件方法
    void outputToFile() {
        try {
            JFileChooser fileChooser = new JFileChooser(); // 文件选择器
            int choice = fileChooser.showSaveDialog(this); // 打开保存对话框

            if (choice == JFileChooser.APPROVE_OPTION) { // 如果点击了保存
                File file = fileChooser.getSelectedFile(); // 获取选择的文件
                PrintWriter writer = new PrintWriter(new FileWriter(file)); // 创建写入文件的打印写入对象
                writer.println(exerciseTextArea.getText()); // 写入内容
                writer.close(); // 关闭写入器
                JOptionPane.showMessageDialog(this, "结果已成功写入文件：" + file.getAbsolutePath()); // 提示写入成功
            }
        } catch (IOException e) { // 异常处理
            JOptionPane.showMessageDialog(this, "写入文件时出现错误！");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(MathExerciseGenerator::new); // 创建并显示窗口
    }
}







